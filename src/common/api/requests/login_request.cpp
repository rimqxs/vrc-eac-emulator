#include "login_request.h"

#include <common/api/json_helper.h>
#include <common/api/session_id.h>

nlohmann::json login_request::serialize(nlohmann::json& json) {
	json = request::serialize(json);
	json["api_version"] = api_version;
	json["has_credentials"] = has_credentials;
	if (has_credentials) {
		json["credentials"]["ApiVersion"] = credentials.ApiVersion;
		json_helper::serialize(json["credentials"], "Token", credentials.Token);
		json["credentials"]["Type"] = credentials.Type;
	}

	json["has_login_info"] = has_login_info;
	if (has_login_info) {
		json["user_login_info"]["ApiVersion"] = user_login_info.ApiVersion;
		json_helper::serialize(json["user_login_info"], "DisplayName", user_login_info.DisplayName);
		json_helper::serialize(json["user_login_info"], "NsaIdToken", user_login_info.NsaIdToken);
	}

	return json;
}

void login_request::deserialize(nlohmann::json json) {
	api_version = json["api_version"];
	has_credentials = json["has_credentials"];
	if (has_credentials) {
		credentials.ApiVersion = json["credentials"]["ApiVersion"];
		json_helper::deserialize(json["credentials"], "Token", credentials.Token);
		credentials.Type = json["credentials"]["Type"];
	}

	has_login_info = json["has_login_info"];
	if (has_login_info) {
		user_login_info.ApiVersion = json["user_login_info"]["ApiVersion"];
		json_helper::deserialize(json["user_login_info"], "DisplayName", user_login_info.DisplayName);
		json_helper::deserialize(json["user_login_info"], "NsaIdToken", user_login_info.NsaIdToken);
	}
}

unsigned char login_request::get_id() {
	return LOGIN_REQ_ID;
}
