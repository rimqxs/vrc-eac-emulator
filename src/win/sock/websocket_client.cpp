#include "websocket_client.h"

#include <format>
#include <functional>

#include "common/protocol/packet_codec.h"
#include "plog/Log.h"

void websocket_client::handle_receive(std::string const& msg) {
	read_stream stream(msg.data(), msg.size());
	auto packet = packet_codec::decode(stream);
	if (packet == nullptr) {
		PLOGF.printf("packet decoding failed");
		return;
	}

	if (handler == nullptr) {
		PLOGF.printf("Handler is not available!");
		return;
	}
	auto handler_func = handler->get_handler_registry().try_get_handler(packet->get_id());
	if (!handler_func.has_value()) {
		PLOGF.printf("Invalid packet is going to be handled: %d", packet->get_id());
		return;
	}
	handler_func.value()(packet);
	stream.close();
}

void websocket_client::run(std::string const& server_address, int port) {
	std::string wsAddress = std::format("ws://{}:{}", server_address, port);
	PLOGI.printf("Connecting to the server: %s", wsAddress.c_str());

	client.onopen = []() {
		PLOGD.printf("Connection established!");
	};
	client.onclose = []() {
		PLOGD.printf("Connection closed");
	};
	client.onmessage = [&](const std::string& msg) {
		handle_receive(msg);
	};

	reconn_setting_t reconn;
	reconn_setting_init(&reconn);
	reconn.delay_policy = 0;
	reconn.min_delay = 3000;
	client.setReconnect(&reconn);

	client.open(wsAddress.c_str());
	while (!client.isConnected()) {
		Sleep(100);
	}
}

void websocket_client::set_packet_handler(std::shared_ptr<packet_handler> handler) {
	this->handler = handler;
}

hv::WebSocketClient& websocket_client::getWebsocketClient() {
	return client;
}
