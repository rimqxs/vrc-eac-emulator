#pragma once
#include <memory>

#include "protocol/packet.h"

class client_packet_processor {
public:
    static void handle(std::shared_ptr<packet> packet);
};
