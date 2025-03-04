#include "id2string_response.h"

#include <common/api/json_helper.h>
#include <common/api/session_id.h>

nlohmann::json id2string_response::serialize(nlohmann::json& json) {
	json = response::serialize(json);
	json["result"] = result;
	json_helper::serialize(json, "buffer", buffer);
	json["buffer_size"] = buffer_size;

	return json;
}

void id2string_response::deserialize(nlohmann::json json) {
	result = json["result"];
	json_helper::deserialize(json, "buffer", buffer);
	buffer_size = json["buffer_size"];
}

unsigned char id2string_response::get_id() {
	return ID2STRING_RES_ID;
}
