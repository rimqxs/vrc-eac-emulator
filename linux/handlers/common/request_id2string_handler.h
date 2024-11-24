#pragma once
#include "protocol/packet.h"

class request_id2string_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
