#include "server.h"

#include <future>
#include <plog/Log.h>

#include "socket.h"
#include "constants.h"
#include "protocol/packet_codec.h"
#include "handlers/handler_registry.h"

SOCKET clientSocket;
std::mutex mutex;
std::vector<std::shared_ptr<packet> > queued_packet;

#define DEFAULT_BUFLEN 512

void server::receive_loopback() {
	handler_registry::init();

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

		read_stream stream(buf, received_len);
		while (stream.bytes_remaining() > 0) {
			auto packet = packet_codec::decode(stream);
			if (packet == nullptr) {
				PLOGF.printf("packet decoding failed");
				return;
			}

			if (const auto handler
				= handler_registry::get_handler_by_id(packet->get_id())) {
				handler(packet);
			}
		}
		stream.close();
	}
}

void server::send_loopback() {
	bool running = true;
	while (running) {
		mutex.lock();
		for (auto& packet : queued_packet) {
			write_stream stream = packet_codec::encode(packet);

			auto buf = stream.as_buffer();
			if (socket::send(clientSocket, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
				PLOGD.printf("Send failed");
				running = false;
			}
			buf.free();

			PLOGD.printf("Packet sent: name=%s id=%d", packet->get_name().c_str(), packet->get_id());
		}
		queued_packet.clear();
		mutex.unlock();

		Sleep(100);
	}
}

void server::run() {
	if (socket::init() != NULL) {
		PLOGE.printf("socks::init failed");
		return;
	}

	SOCKET socket_;
	addrinfo* info;
	if (socket::listen(HOST_PORT, &socket_, &info) != NULL) {
		PLOGE.printf("Server setup failed");
		return;
	}

	PLOGI.printf("Server started on localhost:%d! Waiting for connection...", HOST_PORT);
	if (socket::accept(socket_, &clientSocket) != NULL) {
		PLOGE.printf("Accepting client connection failed");
		return;
	}

	std::thread(send_loopback).detach();
	std::thread(receive_loopback).detach();

	PLOGD.printf("A connection established");
}

void server::send_packet(const std::shared_ptr<packet>& packet) {
	queued_packet.push_back(packet);
}