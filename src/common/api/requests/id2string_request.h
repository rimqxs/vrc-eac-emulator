#pragma once

#include <common/api/request.h>
#include <common/eos/eos_api.h>

class id2string_request : public request {
public:
	EOS_ProductUserId user_id;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
