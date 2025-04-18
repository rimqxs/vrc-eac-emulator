#pragma once

#include <memory>

#include "../handler/packet_handler.h"
#include "common/socket.h"

class sock_client {
	std::shared_ptr<packet_handler> handler;
	SOCKET client_socket;

	void run_receive_loopback();

public:
	sock_client(std::shared_ptr<packet_handler> handler);

	void run(std::string const& server_address, int port);

	SOCKET get_socket();
};
