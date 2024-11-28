#pragma once
#include "protocol/packet.h"

class notify_message_to_server_handler {
public:
	static void handle(std::shared_ptr<packet> packet);
};
