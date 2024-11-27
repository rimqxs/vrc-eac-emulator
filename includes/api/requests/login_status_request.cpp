#include "login_status_request.h"

nlohmann::json login_status_request::serialize(nlohmann::json& json) {
	json = request::serialize(json);
	json["user_id"] = user_id;

	return json;
}

void login_status_request::deserialize(nlohmann::json json) {
	user_id = json["user_id"];
}

unsigned char login_status_request::get_id() {
	return LOGIN_STATUS_REQ_ID;
}
