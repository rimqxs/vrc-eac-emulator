#pragma once

#include <common/protocol/packet.h>

class socket_server {
	static void receive_loopback();

   public:
	static void launch(int port);

	static void send_packet(const std::shared_ptr<packet>& packet);

	static void tick();

   private:
	static void performSend();

	static void performReceive();
};
