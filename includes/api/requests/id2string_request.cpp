#include "id2string_request.h"

#include "api/session_id.h"

nlohmann::json id2string_request::serialize(nlohmann::json& json) {
	json = request::serialize(json);
	json["session_id"] = session_id;
	json["user_id"] = user_id;

	return json;
}

void id2string_request::deserialize(nlohmann::json json) {
	session_id = json["session_id"];
	user_id = json["user_id"];
}

unsigned char id2string_request::get_id() {
	return ID2STRING_REQ_ID;
}
