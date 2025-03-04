#include "begin_session_packet.h"

void begin_session_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(api_version);
	stream.write_as<EOS_ProductUserId>(user_id);
	stream.write_as<EOS_EAntiCheatClientMode>(mode);
}

void begin_session_packet::decode(read_stream& stream) {
	api_version = stream.read_as<int32_t>();
	user_id = stream.read_as<EOS_ProductUserId>();
	mode = stream.read_as<EOS_EAntiCheatClientMode>();
}

std::string begin_session_packet::get_name() {
	return "begin_session";
}

unsigned char begin_session_packet::get_id() {
	return BEGIN_SESSION_PACKET_ID;
}
