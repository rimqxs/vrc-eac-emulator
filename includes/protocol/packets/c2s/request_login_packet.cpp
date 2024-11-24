#include "request_login_packet.h"

void request_login_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(session_id);
	stream.write_as<int32_t>(api_version);

	stream.write_as<bool>(has_credentials);
	if (has_credentials) {
		stream.write_as<int32_t>(credentials.ApiVersion);
		stream.write_string(credentials.Token);
		stream.write_as<int>(credentials.Type);
	}

	stream.write_as<bool>(has_login_info);
	if (has_login_info) {
		stream.write_as<int32_t>(user_login_info.ApiVersion);
		stream.write_string(user_login_info.DisplayName);
		stream.write_string(user_login_info.NsaIdToken);
	}
}

void request_login_packet::decode(read_stream& stream) {
	session_id = stream.read_as<int32_t>();
	api_version = stream.read_as<int32_t>();

	has_credentials = stream.read_as<bool>();
	if (has_credentials) {
		credentials.ApiVersion = stream.read_as<int32_t>();
		credentials.Token = stream.read_string();
		credentials.Type = stream.read_as<int>();
	}

	has_login_info = stream.read_as<bool>();
	if (has_login_info) {
		user_login_info.ApiVersion = stream.read_as<int32_t>();
		user_login_info.DisplayName = stream.read_string();
		user_login_info.NsaIdToken = stream.read_string();
	}
}

std::string request_login_packet::get_name() {
	return "request_login";
}

unsigned char request_login_packet::get_id() {
	return REQUEST_LOGIN_PACKET_ID;
}
