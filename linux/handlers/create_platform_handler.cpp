#include "create_platform_handler.h"

#include "../eos/eos_platform.h"
#include "eos/eos_platform_types.h"
#include "protocol/packets/c2s/create_platform_packet.h"

void create_platform_handler::handle(std::shared_ptr<packet> packet) {
	auto create_platform = std::static_pointer_cast<create_platform_packet>(packet);

	EOS_Platform_Options options{};
	options.ApiVersion = create_platform->api_version;
	options.Reserved = nullptr; // It should be always NULL
	options.ProductId = create_platform->product_id.c_str();
	options.SandboxId = create_platform->sandbox_id.c_str();
	options.ClientCredentials.ClientId = create_platform->client_credentials.client_id.c_str();
	options.ClientCredentials.ClientSecret = create_platform->client_credentials.client_secret.c_str();
	options.bIsServer = create_platform->is_server;
	options.EncryptionKey = create_platform->encryption_key.c_str();
	options.OverrideCountryCode = create_platform->override_country_code.c_str();
	options.OverrideLocaleCode = create_platform->override_locale_code.c_str();
	options.DeploymentId = create_platform->deployment_id.c_str();
	options.Flags = create_platform->flags;
	options.CacheDirectory = create_platform->cache_directory.c_str();
	options.TickBudgetInMilliseconds = create_platform->tick_budget_in_milliseconds;

	options.RTCOptions = nullptr;
	EOS_Platform_RTCOptions rtc_options{};
	if (create_platform->has_rtc_options) {
		rtc_options.ApiVersion = create_platform->rtc_options.api_version;
		rtc_options.PlatformSpecificOptions = nullptr;
		rtc_options.BackgroundMode = create_platform->rtc_options.background_mode;

		options.RTCOptions = &rtc_options;
	}

	options.IntegratedPlatformOptionsContainerHandle = nullptr;
	options.SystemSpecificOptions = nullptr;

	options.TaskNetworkTimeoutSeconds = nullptr;
	double task_network_timeout_seconds = 0.0;
	if (create_platform->has_task_network_timeout_seconds_value) {
		task_network_timeout_seconds = create_platform->task_network_timeout_seconds;
		options.TaskNetworkTimeoutSeconds = &task_network_timeout_seconds;
	}

	eos_platform::create_platform(options);
	PLOGI.printf("Platform Created: product_id=%s, client_id=%s", create_platform->product_id.c_str(), create_platform->client_credentials.client_id.c_str());
}
