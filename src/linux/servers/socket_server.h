#pragma once

#include <common/protocol/packet.h>

class socket_server {
    static void receive_loopback();
public:
    static void launch();

    static void send_packet(const std::shared_ptr<packet>& packet);

	static void tick();
};
