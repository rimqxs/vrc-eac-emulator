#pragma once
#include "protocol/packet.h"

class notify_message_to_server_packet : public packet  {
public:
	bool require_bind;

	struct {
		int32_t ApiVersion;
	} options;

	nullable_string base64_message_data;
	uint32_t message_data_size;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
