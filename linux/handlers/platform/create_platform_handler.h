#pragma once
#include "protocol/packet.h"

class create_platform_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};