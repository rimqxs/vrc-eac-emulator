#pragma once
#include "protocol/packet.h"

class initialize_eos_packet : public packet {
public:
	int32_t api_version;
	nullable_string product_name;
	nullable_string product_version;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
