#pragma once

#include <common/protocol/packet.h>
#include <common/protocol/stream/read_stream.h>
#include <common/protocol/stream/write_stream.h>

#include <cstdint>

class end_session_packet : public packet {
public:
	struct {
		int32_t ApiVersion;
	} options;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
