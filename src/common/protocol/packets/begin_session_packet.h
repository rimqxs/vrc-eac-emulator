#pragma once

#include <common/eos/eos_api.h>
#include <common/protocol/packet.h>
#include <common/protocol/stream/write_stream.h>
#include <common/protocol/stream/read_stream.h>
#include <cstdint>

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
