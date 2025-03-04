#pragma once

#include "json.hpp"

class response {
public:
	virtual ~response() = default;

	virtual nlohmann::json serialize(nlohmann::json& json) {
		json["id"] = get_id();
		return json;
	}

	virtual void deserialize(nlohmann::json json) = 0;

	virtual unsigned char get_id() = 0;
};
