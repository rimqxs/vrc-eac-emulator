#pragma once

#include <functional>
#include <map>
#include <memory>
#include <optional>

#include "common/protocol/packet.h"

class handler_registry {
	std::map<unsigned char, std::function<void(std::shared_ptr<packet>)>> handlers;

public:
	void register_handler(unsigned char packet_id, std::function<void(std::shared_ptr<packet>)> handler);

	std::optional<std::function<void(std::shared_ptr<packet>)>> try_get_handler(unsigned char packet_id);
};
