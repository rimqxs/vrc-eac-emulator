#include "socket_server.h"

#include <future>
#include <plog/Log.h>

#include <common/socket.h>
#include <common/constants.h>
#include <common/protocol/packet_codec.h>
#include <httplib.h>

#include "../handlers/handler_registry.h"

SOCKET clientSocket;
std::mutex send_mutex, receive_mutex;
std::vector<std::shared_ptr<packet> > send_queued_packets, receive_queued_packets;

void socket_server::launch() {
	if (socket::init() != NULL) {
		PLOGE.printf("socks::init failed");
		return;
	}

	SOCKET socket_;
	addrinfo* info;
	if (socket::listen(HOST_SOCKET_PORT, &socket_, &info) != NULL) {
		PLOGE.printf("Server setup failed");
		return;
	}

	PLOGI.printf("Server started on localhost:%d! Waiting for connection...", HOST_SOCKET_PORT);
	if (socket::accept(socket_, &clientSocket) != NULL) {
		PLOGE.printf("Accepting client connection failed");
		return;
	}

	std::thread(receive_loopback).detach();

	PLOGD.printf("A connection established");
}

void socket_server::send_packet(const std::shared_ptr<packet>& packet) {
	send_mutex.lock();
	send_queued_packets.push_back(packet);
	send_mutex.unlock();
}

void socket_server::receive_loopback() {
	bool running = true;
	char buf[DEFAULT_BUFLEN];
	int buf_len = DEFAULT_BUFLEN;
	while (running) {
		int received_len = recv(clientSocket, buf, buf_len, 0);
		if (received_len <= 0) {
			PLOGW.printf("Connection closed");
			running = false;
			continue;
		}

		receive_mutex.lock();
		read_stream stream(buf, received_len);
		while (stream.bytes_remaining() > 0) {
			auto packet = packet_codec::decode(stream);
			if (packet == nullptr) {
				PLOGF.printf("packet decoding failed");
				return;
			}

			receive_queued_packets.push_back(packet);
		}
		stream.close();
		receive_mutex.unlock();
	}
}

void socket_server::tick() {
	// perform receiving
	receive_mutex.lock();
	for (const auto& packet : receive_queued_packets) {
		if (const auto handler
			= handler_registry::get_handler_by_id(packet->get_id())) {
			handler(packet);
		}
	}
	receive_queued_packets.clear();
	receive_mutex.unlock();

	// perform sending
	send_mutex.lock();
	for (auto& packet : send_queued_packets) {
		write_stream stream = packet_codec::encode(packet);

		auto buf = stream.as_buffer();
		if (socket::send(clientSocket, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
			PLOGD.printf("Send failed");
			return;
		}
		buf.free();

		PLOGD.printf("Packet sent: name=%s id=%d", packet->get_name().c_str(), packet->get_id());
	}
	send_queued_packets.clear();
	send_mutex.unlock();
}
