#pragma once
#include "nullable_string.h"
#include "eos/eos_api.h"
#include "protocol/packet.h"

class response_id2string_packet : public packet {
public:
	int session_id;
	EOS_EResult result;
	nullable_string buffer;
	int32_t buffer_size;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
