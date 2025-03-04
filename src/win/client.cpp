#include "client.h"

#include <plog/Log.h>

#include <future>

#include "client_packet_processor.h"
#include "common/api/session_factory.h"
#include "common/constants.h"
#include "common/protocol/packet_codec.h"
#include "common/protocol/packets/handshake_packet.h"
#include "common/socket.h"
#include "httplib.h"

SOCKET socket_;
std::mutex mutex;
std::vector<std::shared_ptr<packet>> queued_packet;

#define DEFAULT_BUFLEN 10000

void client::receive_loopback() {
	bool running = true;
	char buf[DEFAULT_BUFLEN];
	int buf_len = DEFAULT_BUFLEN;
	while (running) {
		int received_len = recv(socket_, buf, buf_len, 0);
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

			client_packet_processor::handle(packet);
		}
		stream.close();
	}
}

void client::send_loopback() {
	bool running = true;
	while (running) {
		mutex.lock();
		for (auto& packet : queued_packet) {
			write_stream stream = packet_codec::encode(packet);

			auto buf = stream.as_buffer();
			if (socket::send(socket_, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
				PLOGD.printf("Send failed");
				running = false;
			}
			buf.free();

			PLOGD.printf("Packet sent: name=%s id=%d", packet->get_name().c_str(), packet->get_id());
		}
		queued_packet.clear();
		mutex.unlock();

		Sleep(30);
	}
}

void client::connect() {
	if (socket::init() != NULL) {
		PLOGE.printf("socks::init failed");
		return;
	}

	PLOGD.printf("Connecting to the server %s:%d!", HOST_IP_ADDR, HOST_SOCKET_PORT);
	while (socket::connect(HOST_IP_ADDR, HOST_SOCKET_PORT, &socket_)) {
		PLOGW.printf("socks::connect failed, retrying after 5 seconds...");
		Sleep(5000);
	}
	PLOGI.printf("Connected to the server!");

	std::thread(send_loopback).detach();
	std::thread(receive_loopback).detach();

	// Send handshake packet
	auto packet = std::make_shared<handshake_packet>();
	packet->timestamp = std::time(nullptr);
	send_packet(packet);
}

void client::send_packet(const std::shared_ptr<packet>& packet) {
	mutex.lock();
	queued_packet.push_back(packet);
	mutex.unlock();
}

std::shared_ptr<response> client::_request(std::shared_ptr<::request> const& request) {
	httplib::Client client(std::format("http://{}:{}", HOST_IP_ADDR, HOST_HTTP_PORT));

	nlohmann::json serialized;
	request->serialize(serialized);

	auto res = client.Post("/task", serialized.dump(), "application/json");
	if (res->status != 200) {
		PLOGE.printf("[HTTP] The server has returned an error: %d", res->status);
		return nullptr;
	}

	nlohmann::json json = nlohmann::json::parse(res->body);
	PLOGI.printf("[HTTP] Response received: %s", json.dump().c_str());

	auto response = session_factory::create_response(json["id"]);
	if (response == nullptr) {
		PLOGF.printf("Invalid request id: %d", json["id"]);
		return nullptr;
	}
	response->deserialize(json);

	return response;
}

void client::tick() {
	// TODO: Impl
}
