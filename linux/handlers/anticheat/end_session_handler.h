#pragma once
#include "protocol/packet.h"

class end_session_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
