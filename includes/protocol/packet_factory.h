#pragma once

#include <memory>

#include "packet.h"

#define CREATE_PKT(type) return std::make_shared<type>()

class packet_factory {
public:
    static std::shared_ptr<packet> create_packet(unsigned char id);
};
