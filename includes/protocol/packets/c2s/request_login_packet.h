#pragma once
#include "protocol/packet.h"

#include <string>

class request_login_packet : public packet {
public:
	int32_t api_version;
	bool has_credentials;
	struct {
		int32_t ApiVersion;
		nullable_string Token;
		int Type;
	} credentials;
	bool has_login_info;
	struct {
		int32_t ApiVersion;
		nullable_string DisplayName;
		nullable_string NsaIdToken;
	} user_login_info;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
