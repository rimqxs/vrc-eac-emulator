#pragma once
#include "protocol/packet.h"

class request_login_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
