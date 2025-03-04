#include "receive_message_packet.h"

void receive_message_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(api_version);
	stream.write_string(base64_message);
	stream.write_as<uint32_t>(data_length_bytes);
}

void receive_message_packet::decode(read_stream& stream) {
	api_version = stream.read_as<int32_t>();
	base64_message = stream.read_string();
	data_length_bytes = stream.read_as<uint32_t>();
}

std::string receive_message_packet::get_name() {
	return "receive_message";
}

unsigned char receive_message_packet::get_id() {
	return RECEIVE_MESSAGE_PACKET_ID;
}
