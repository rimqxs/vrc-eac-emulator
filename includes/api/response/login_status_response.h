#pragma once
#include "api/response.h"
#include "eos/eos_api.h"

class login_status_response : public response {
public:
	EOS_ELoginStatus status;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
