#pragma once
#include "protocol/packet.h"

class receive_message_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
