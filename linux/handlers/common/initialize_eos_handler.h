#pragma once
#include "protocol/packet.h"

class initialize_eos_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
