#include "id2string_response.h"

#include "api/session_id.h"
#include "api/json_helper.h"

nlohmann::json id2string_response::serialize(nlohmann::json& json) {
	json = response::serialize(json);
	json["session_id"] = session_id;
	json["result"] = result;
	json_helper::serialize(json, "buffer", buffer);
	json["buffer_size"] = buffer_size;

	return json;
}

void id2string_response::deserialize(nlohmann::json json) {
	session_id = json["session_id"];
	result = json["result"];
	json_helper::deserialize(json, "buffer", buffer);
	buffer_size = json["buffer_size"];
}

unsigned char id2string_response::get_id() {
	return ID2STRING_RES_ID;
}
