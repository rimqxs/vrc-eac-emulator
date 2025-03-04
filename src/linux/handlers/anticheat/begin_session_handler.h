#pragma once

#include "common/protocol/packet.h"

class begin_session_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
