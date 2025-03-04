#include "notify_message_to_server_packet.h"

void notify_message_to_server_packet::encode(write_stream& stream) {
	stream.write_as<bool>(require_bind);
	if (require_bind) {
		stream.write_as<int32_t>(options.ApiVersion);
	} else {
		stream.write_string(base64_message_data);
		stream.write_as<uint32_t>(message_data_size);
	}
}

void notify_message_to_server_packet::decode(read_stream& stream) {
	require_bind = stream.read_as<bool>();
	if (require_bind) {
		options.ApiVersion = stream.read_as<int32_t>();
	} else {
		base64_message_data = stream.read_string();
		message_data_size = stream.read_as<uint32_t>();
	}
}

std::string notify_message_to_server_packet::get_name() {
	return "notify_message_to_server";
}

unsigned char notify_message_to_server_packet::get_id() {
	return NOTIFY_MESSAGE_TO_SERVER_PACKET_ID;
}
