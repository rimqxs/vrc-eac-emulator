#include "initialize_eos_packet.h"

void initialize_eos_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(api_version);
	stream.write_string(product_name);
	stream.write_string(product_version);
}

void initialize_eos_packet::decode(read_stream& stream) {
	api_version = stream.read_as<int32_t>();
	product_name = stream.read_string();
	product_version = stream.read_string();
}

std::string initialize_eos_packet::get_name() {
	return "initialize_eos";
}

unsigned char initialize_eos_packet::get_id() {
	return INITIALIZE_EOS_PACKET_ID;
}
