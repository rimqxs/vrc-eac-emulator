#include "end_session_packet.h"

void end_session_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(options.ApiVersion);
}

void end_session_packet::decode(read_stream& stream) {
	options.ApiVersion = stream.read_as<int32_t>();
}

std::string end_session_packet::get_name() {
	return "end_session";
}

unsigned char end_session_packet::get_id() {
	return END_SESSION_PACKET_ID;
}
