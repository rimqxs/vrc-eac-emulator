#pragma once

#include <hv/WebSocketClient.h>

#include <memory>

#include "../handler/packet_handler.h"

class websocket_client {
	hv::WebSocketClient client;

	std::shared_ptr<packet_handler> handler;

	void handle_receive(std::string const& msg);

public:
	void run(std::string const& server_address, int port);

	void set_packet_handler(std::shared_ptr<packet_handler> handler);

	hv::WebSocketClient& getWebsocketClient();
};
