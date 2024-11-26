#pragma once
#include "api/request.h"
#include "eos/eos_api.h"

class id2string_request : public request {
public:
	int session_id;
	EOS_ProductUserId user_id;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
