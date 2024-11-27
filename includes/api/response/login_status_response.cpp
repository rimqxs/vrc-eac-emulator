//
// Created by ericdoa on 24/11/27.
//

#include "login_status_response.h"

nlohmann::json login_status_response::serialize(nlohmann::json& json) {
	json = response::serialize(json);
	json["status"] = status;

	return json;
}

void login_status_response::deserialize(nlohmann::json json) {
	status = json["status"];
}

unsigned char login_status_response::get_id() {
	return LOGIN_STATUS_RES_ID;
}
