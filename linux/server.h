#pragma once
#include "protocol/packet.h"

class server {
    static void receive_handler();

    static void send_handler();
public:
    static void run();

    static void send_packet(const std::shared_ptr<packet>& packet);
};
