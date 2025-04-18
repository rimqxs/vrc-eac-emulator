#include "handler_registry.h"

#include <optional>

void handler_registry::register_handler(unsigned char packet_id, std::function<void(std::shared_ptr<packet>)> handler) {
	handlers[packet_id] = handler;
}

std::optional<std::function<void(std::shared_ptr<packet>)>> handler_registry::try_get_handler(unsigned char packet_id) {
	return handlers.contains(packet_id) ? handlers[packet_id] : std::optional<std::function<void(std::shared_ptr<packet>)>>();
}
