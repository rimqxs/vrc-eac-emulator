#include "../client.h"
#include "common/eos/eos_api.h"
#include "common/eos/eos_platform_types.h"
#include "common/protocol/packets/create_platform_packet.h"

EOS_DECLARE_FUNC(EOS_HPlatform)
DummyEOS_Platform_Create(EOS_Platform_Options* options) {
	auto packet = std::make_shared<create_platform_packet>();
	packet->api_version = options->ApiVersion;
	packet->product_id = nullable_string(options->ProductId);
	packet->sandbox_id = nullable_string(options->SandboxId);
	packet->client_credentials.client_id = nullable_string(options->ClientCredentials.ClientId);
	packet->client_credentials.client_secret = nullable_string(options->ClientCredentials.ClientSecret);
	packet->is_server = options->bIsServer;
	packet->encryption_key = nullable_string(options->EncryptionKey);
	packet->override_country_code = nullable_string(options->OverrideCountryCode);
	packet->override_locale_code = nullable_string(options->OverrideLocaleCode);
	packet->deployment_id = nullable_string(options->DeploymentId);
	packet->flags = options->Flags;
	packet->cache_directory = nullable_string(options->CacheDirectory);
	packet->tick_budget_in_milliseconds = options->TickBudgetInMilliseconds;

	packet->has_rtc_options = options->RTCOptions != nullptr;
	if (options->RTCOptions != nullptr) {
		packet->rtc_options.api_version = options->RTCOptions->ApiVersion;
		packet->rtc_options.background_mode = options->RTCOptions->BackgroundMode;
	}

	packet->has_task_network_timeout_seconds_value = options->TaskNetworkTimeoutSeconds != nullptr;
	if (options->TaskNetworkTimeoutSeconds != nullptr) {
		packet->task_network_timeout_seconds = *options->TaskNetworkTimeoutSeconds;
	}

	client::send_packet(packet);

	return 0x28B857C4A60;
}

EOS_DECLARE_FUNC(void)
DummyEOS_Platform_Tick(EOS_HPlatform handle) {
}

EOS_DECLARE_FUNC(EOS_HConnect)
DummyEOS_Platform_GetConnectInterface(EOS_HPlatform handle) {
	PLOG_INFO.printf("EOS_Platform_GetConnectInterface called");
	return 0x30A129C4A60;
}

EOS_DECLARE_FUNC(EOS_HAntiCheatClient)
DummyEOS_Platform_GetAntiCheatClientInterface(EOS_HPlatform handle) {
	PLOG_INFO.printf("EOS_Platform_GetAntiCheatClientInterface called");
	return 0x12B139C4A40;
}
