#pragma once
#include "protocol/packet.h"

class receive_message_packet : public packet {
public:
	int32_t api_version;
	nullable_string base64_message;
	uint32_t data_length_bytes;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
