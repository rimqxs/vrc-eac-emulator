#pragma once

#include <memory>
#include <mutex>

#include "common/protocol/packet.h"
#include "common/socket.h"
#include "hv/WebSocketClient.h"

class packet_sender {
	hv::WebSocketClient& websocket_client;
	std::mutex send_mutex;
	std::vector<std::shared_ptr<packet>> queued_packet;

	void run_loopback();

public:
	packet_sender(hv::WebSocketClient& websocket_client);

	void start();

	void send_packet(std::shared_ptr<packet> packet);
};
