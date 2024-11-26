#pragma once
#include "json.hpp"
#include "nullable_string.h"

class json_helper {
public:
	static void serialize(nlohmann::json& json, std::string const& key, nullable_string const& value) {
		if (value == nullptr) {
			return;
		}

		json[key] = value.c_str();
	}

	static void deserialize(nlohmann::json const& json, std::string const& key, nullable_string& val) {
		if (json.find(key) == json.end()) {
			val = nullable_string{};
			return;
		}

		val = nullable_string(json[key].get<std::string>());
	}
};
