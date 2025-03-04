#pragma once

#include "common/protocol/packet.h"

class handshake_packet_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
