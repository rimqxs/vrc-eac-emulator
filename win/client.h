#pragma once

#include "protocol/packet.h"

class client {
    static void receive_handler();

    static void send_handler();
public:
    static void connect();

    static void send_packet(const std::shared_ptr<packet>& packet);
};
