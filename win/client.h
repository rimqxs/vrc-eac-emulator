#pragma once

#include "protocol/packet.h"

class client {
public:
    static void connect();

    static void send_packet(const std::shared_ptr<packet>& packet);
};
