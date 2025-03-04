#pragma once

#include <nullable_string.h>
#include <common/api/request.h>

class login_request : public request {
public:
	int32_t api_version;
	bool has_credentials;
	struct {
		int32_t ApiVersion;
		nullable_string Token;
		int Type;
	} credentials;
	bool has_login_info;
	struct {
		int32_t ApiVersion;
		nullable_string DisplayName;
		nullable_string NsaIdToken;
	} user_login_info;

	nlohmann::json serialize(nlohmann::json& json) override;

	void deserialize(nlohmann::json json) override;

	unsigned char get_id() override;
};
