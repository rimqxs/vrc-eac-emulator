#include <eos/eos_api.h>

#include "eos.h"
#include "../client.h"
#include "eos/eos_general_types.h"
#include "protocol/packets/c2s/initialize_eos_packet.h"
#include "protocol/packets/c2s/request_id2string_packet.h"

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

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_ProductUserId_ToString(EOS_ProductUserId account_id, char* out_buffer, int32_t* in_out_buffer_length) {
	static int session_id = 1000;
	auto packet = std::make_shared<request_id2string_packet>();
	packet->session_id = session_id++;
	packet->user_id = account_id;
	client::send_packet(packet);

	auto result = eos::wait_for_id2string(packet->session_id);
	auto buffer = std::get<1>(result);
	auto buffer_size = std::get<2>(result);
	if (buffer != nullptr) {
		ZeroMemory(out_buffer, *in_out_buffer_length);
		memcpy(out_buffer, buffer.c_str(), buffer_size + 1);
	}
	*in_out_buffer_length = buffer_size;
	PLOGI.printf("Writing: ProductUserId=%s len=%d", buffer.c_str(), buffer_size);

	return std::get<0>(result);
}

// IDK what this function does, but it's called by gameassembly.dll
EOS_DECLARE_FUNC(bool) DummyEOS_EResult_IsOperationComplete(EOS_EResult result) {
	return true;
}
