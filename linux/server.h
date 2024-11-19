#pragma once
#include "protocol/packet.h"

class server {
public:
    static void run();

    static void send_packet(const std::shared_ptr<packet>& packet);
};
