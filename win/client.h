#pragma once

#include "protocol/packet.h"

class client {
    static void receive_loopback();

    static void send_loopback();
public:
    static void connect();

    static void send_packet(const std::shared_ptr<packet>& packet);
};
