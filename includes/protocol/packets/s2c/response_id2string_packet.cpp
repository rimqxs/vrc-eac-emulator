#include "response_id2string_packet.h"

void response_id2string_packet::encode(write_stream& stream) {
	stream.write_as<int>(session_id);
	stream.write_as<EOS_EResult>(result);
	stream.write_string(buffer);
	stream.write_as<int32_t>(buffer_size);
}

void response_id2string_packet::decode(read_stream& stream) {
	session_id = stream.read_as<int>();
	result = stream.read_as<EOS_EResult>();
	buffer = stream.read_string();
	buffer_size = stream.read_as<int32_t>();
}

std::string response_id2string_packet::get_name() {
	return "response_id2string_packet";
}

unsigned char response_id2string_packet::get_id() {
	return RESPONSE_ID2STRING_PACKET_ID;
}
