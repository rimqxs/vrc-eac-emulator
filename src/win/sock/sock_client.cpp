#include "sock_client.h"

#include <functional>
#include <thread>

#include "common/protocol/packet_codec.h"
#include "plog/Log.h"

void sock_client::run_receive_loopback() {
	while (true) {
		std::vector<char> received_buffer = socket::recv(client_socket);
		if (received_buffer.size() <= 0) {
			PLOGW.printf("Connection closed");
			continue;
		}
		read_stream stream(received_buffer.data(), received_buffer.size());
		while (stream.bytes_remaining() > 0) {
			auto packet = packet_codec::decode(stream);
			if (packet == nullptr) {
				PLOGF.printf("packet decoding failed");
				continue;
			}
			auto handler_func = handler->get_handler_registry().try_get_handler(packet->get_id());
			if (!handler_func.has_value()) {
				PLOGF.printf("Invalid packet is going to be handled: %d", packet->get_id());
				continue;
			}
			handler_func.value()(packet);
		}
		stream.close();
	}
}

sock_client::sock_client(std::shared_ptr<packet_handler> handler) : handler(handler) {
}

void sock_client::run(std::string const& server_address, int port) {
	PLOGI.printf("Connection to Server on %s:%d", server_address.c_str(), port);
	if (socket::init() != NULL) {
		PLOGE.printf("socks::init failed");
		return;
	}

	PLOGD.printf("Connecting to the server %s:%d!", server_address.c_str(), port);
	while (socket::connect(server_address.c_str(), port, &client_socket)) {
		PLOGW.printf("socks::connect failed, retrying after 5 seconds...");
		Sleep(5000);
	}
	PLOGI.printf("Connected to the server!");

	std::thread(std::bind(&sock_client::run_receive_loopback, this)).detach();
}

SOCKET sock_client::get_socket() {
	return client_socket;
}
