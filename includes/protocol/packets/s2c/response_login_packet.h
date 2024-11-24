#pragma once
#include "eos/eos_api.h"
#include "protocol/packet.h"

class response_login_packet : public packet {
public:
	int session_id;
	EOS_EResult result_code;
	EOS_ProductUserId local_user_id;
	EOS_ContinuanceToken continuance_token;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
