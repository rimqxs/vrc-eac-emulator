#pragma once
#include "eos/eos_api.h"
#include "protocol/packet.h"

class request_id2string_packet : public packet {
public:
	int session_id;
	EOS_ProductUserId user_id;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
