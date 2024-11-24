#include "response_login_packet.h"

void response_login_packet::encode(write_stream& stream) {
	stream.write_as<int>(session_id);
	stream.write_as<EOS_EResult>(result_code);
	stream.write_as<EOS_ProductUserId>(local_user_id);
	stream.write_as<EOS_ContinuanceToken>(continuance_token);
}

void response_login_packet::decode(read_stream& stream) {
	session_id = stream.read_as<int>();
	result_code = stream.read_as<EOS_EResult>();
	local_user_id = stream.read_as<EOS_ProductUserId>();
	continuance_token = stream.read_as<EOS_ContinuanceToken>();
}

std::string response_login_packet::get_name() {
	return "response_login";
}

unsigned char response_login_packet::get_id() {
	return RESPONSE_LOGIN_PACKET_ID;
}