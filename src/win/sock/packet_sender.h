#pragma once

#include <memory>
#include <mutex>

#include "common/protocol/packet.h"
#include "common/socket.h"

class packet_sender {
	SOCKET client_socket;
	std::mutex send_mutex;
	std::vector<std::shared_ptr<packet>> queued_packet;

	void run_loopback();

public:
	void start(SOCKET client);

	void send_packet(std::shared_ptr<packet> packet);
};
