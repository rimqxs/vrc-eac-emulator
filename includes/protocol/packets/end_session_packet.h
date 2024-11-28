#pragma once
#include "protocol/packet.h"

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
