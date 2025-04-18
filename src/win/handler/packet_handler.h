#pragma once

#include "handler_registry.h"

class packet_handler {
public:
	~packet_handler() = default;

	virtual void on_connected() = 0;

	virtual handler_registry& get_handler_registry() = 0;
};
