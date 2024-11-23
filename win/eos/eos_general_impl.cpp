#include <eos/eos_api.h>

#include "../client.h"
#include "eos/eos_general_types.h"
#include "protocol/packets/c2s/initialize_eos_packet.h"

EOS_DECLARE_FUNC(void) dummy_func() {
    PLOGF.printf("This should never happened");
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Initialize(EOS_InitializeOptions* options) {
	auto packet = std::make_shared<initialize_eos_packet>();
	packet->api_version = options->ApiVersion;
	packet->product_name = nullable_string(options->ProductName);
	packet->product_version = nullable_string(options->ProductVersion);

	client::send_packet(packet);
	PLOGI.printf("EOS_Initialize handled");

    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_ENetworkStatus) DummyEOS_Platform_GetNetworkStatus(EOS_HPlatform handle) {
    return EOS_NS_Online;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Platform_SetApplicationStatus(EOS_HPlatform handle, int newStatus) {
    PLOG_INFO.printf("EOS_Platform_SetApplicationStatus called: newStatus=%d", newStatus);
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Platform_SetNetworkStatus(EOS_HPlatform handle, EOS_ENetworkStatus newStatus) {
    PLOG_INFO.printf("EOS_Platform_SetNetworkStatus called: newStatus=%d", newStatus);
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetCallback(void* callback) {
    return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_Logging_SetLogLevel(int category, int level) {
    return EOS_Success;
}
