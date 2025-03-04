#pragma once

#include <common/api/session_id.h>
#include <json.hpp>

class request {
public:
	virtual ~request() = default;

	virtual nlohmann::json serialize(nlohmann::json& json) {
		json["id"] = get_id();
		return json;
	};

	virtual void deserialize(nlohmann::json json) = 0;

	virtual unsigned char get_id() = 0;
};
