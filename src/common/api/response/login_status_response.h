#pragma once

#include <common/api/response.h>
#include <common/eos/eos_api.h>

class login_status_response : public response {
public:
	EOS_ELoginStatus status;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
