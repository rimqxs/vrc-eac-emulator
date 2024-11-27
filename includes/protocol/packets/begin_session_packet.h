#pragma once
#include "eos/eos_api.h"
#include "protocol/packet.h"

class begin_session_packet : public packet {
public:
	int32_t api_version;
	EOS_ProductUserId user_id;
	EOS_EAntiCheatClientMode mode;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
