#pragma once

#include "nullable_string.h"
#include "protocol/packet.h"

class create_platform_packet : public packet {
public:
	int32_t api_version;
	nullable_string product_id;
	nullable_string sandbox_id;
	struct {
		nullable_string client_id;
		nullable_string client_secret;
	} client_credentials;
	bool is_server;
	nullable_string encryption_key;
	nullable_string override_country_code;
	nullable_string override_locale_code;
	nullable_string deployment_id;
	uint64_t flags;
	nullable_string cache_directory;
	uint32_t tick_budget_in_milliseconds;
	bool has_rtc_options;
	struct {
		int32_t api_version;
		int background_mode;
	} rtc_options;
	bool has_task_network_timeout_seconds_value;
	double task_network_timeout_seconds;

	void encode(write_stream& stream) override;

	void decode(read_stream& stream) override;

	std::string get_name() override;

	unsigned char get_id() override;
};
