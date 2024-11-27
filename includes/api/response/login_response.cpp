#include "login_response.h"


nlohmann::json login_response::serialize(nlohmann::json& json) {
	json = response::serialize(json);
	json["result_code"] = result_code;
	json["local_user_id"] = local_user_id;
	json["continuance_token"] = continuance_token;

	return json;
}

void login_response::deserialize(nlohmann::json json) {
	result_code = json["result_code"].get<int>();
	local_user_id = json["local_user_id"].get<EOS_ProductUserId>();
	continuance_token = json["continuance_token"].get<EOS_ContinuanceToken>();
}

unsigned char login_response::get_id() {
	return LOGIN_RES_ID;
}