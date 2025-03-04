#pragma once

#include "nullable_string.h"
#include <common/api/response.h>
#include <common/eos/eos_api.h>

class id2string_response : public response {
public:
	EOS_EResult result;
	nullable_string buffer;
	int32_t buffer_size;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
