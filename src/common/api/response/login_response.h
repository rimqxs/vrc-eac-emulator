#pragma once

#include <common/api/response.h>
#include <common/eos/eos_api.h>

class login_response : public response {
public:
	EOS_EResult result_code;
	EOS_ProductUserId local_user_id;
	EOS_ContinuanceToken continuance_token;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
