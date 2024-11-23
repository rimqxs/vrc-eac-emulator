#include "create_platform_packet.h"

void create_platform_packet::encode(write_stream& stream) {
	stream.write_as<int32_t>(api_version);
	stream.write_string(product_id);
	stream.write_string(sandbox_id);
	stream.write_string(client_credentials.client_id);
	stream.write_string(client_credentials.client_secret);
	stream.write_as<bool>(is_server);
	stream.write_string(encryption_key);
	stream.write_string(override_country_code);
	stream.write_string(override_locale_code);
	stream.write_string(deployment_id);
	stream.write_as<uint64_t>(flags);
	stream.write_string(cache_directory);
	stream.write_as<uint32_t>(tick_budget_in_milliseconds);

	stream.write_as<bool>(has_rtc_options);
	if (has_rtc_options) {
		stream.write_as<int32_t>(rtc_options.api_version);
		stream.write_as<int>(rtc_options.background_mode);
	}

	stream.write_as<bool>(has_task_network_timeout_seconds_value);
	if (has_task_network_timeout_seconds_value) {
		stream.write_as<double>(task_network_timeout_seconds);
	}
}

void create_platform_packet::decode(read_stream& stream) {
	api_version = stream.read_as<int32_t>();
	product_id = stream.read_string();
	sandbox_id = stream.read_string();
	client_credentials.client_id = stream.read_string();
	client_credentials.client_secret = stream.read_string();
	is_server = stream.read_as<bool>();
	encryption_key = stream.read_string();
	override_country_code = stream.read_string();
	override_locale_code = stream.read_string();
	deployment_id = stream.read_string();
	flags = stream.read_as<uint64_t>();
	cache_directory = stream.read_string();
	tick_budget_in_milliseconds = stream.read_as<uint32_t>();

	has_rtc_options = stream.read_as<bool>();
	if (has_rtc_options) {
		rtc_options.api_version = stream.read_as<int32_t>();
		rtc_options.background_mode = stream.read_as<int>();
	}

	has_task_network_timeout_seconds_value = stream.read_as<bool>();
	if (has_task_network_timeout_seconds_value) {
		task_network_timeout_seconds = stream.read_as<double>();
	}
}

std::string create_platform_packet::get_name() {
	return "create_platform";
}

unsigned char create_platform_packet::get_id() {
	return CREATE_PLATFORM_PACKET_ID;
}
