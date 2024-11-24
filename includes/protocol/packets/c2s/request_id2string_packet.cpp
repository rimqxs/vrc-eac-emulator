#include "request_id2string_packet.h"

void request_id2string_packet::encode(write_stream& stream) {
	stream.write_as<int>(session_id);
	stream.write_as<EOS_ProductUserId>(user_id);
}

void request_id2string_packet::decode(read_stream& stream) {
	session_id = stream.read_as<int>();
	user_id = stream.read_as<EOS_ProductUserId>();
}

std::string request_id2string_packet::get_name() {
	return "request_id2string_packet";
}

unsigned char request_id2string_packet::get_id() {
	return REQUEST_ID2STRING_PACKET_ID;
}
