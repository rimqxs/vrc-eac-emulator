#include <future>

#include "../emulator_client.h"
#include "../emulator_initializer.h"
#include "common/api/requests/id2string_request.h"
#include "common/api/response/id2string_response.h"
#include "common/eos/eos_api.h"
#include "common/eos/eos_general_types.h"
#include "common/protocol/packets/initialize_eos_packet.h"

EOS_DECLARE_FUNC(void)
dummy_func() {
	PLOGF.printf("This should never happened");
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_Initialize(EOS_InitializeOptions* options) {
	auto status = emulator_initializer::init();
	if (status == EmulatorStauts::REQUIRED_CLOSE) {
		system("pause");
		exit(1);
	}

	auto packet = std::make_shared<initialize_eos_packet>();
	packet->api_version = options->ApiVersion;
	packet->product_name = nullable_string(options->ProductName);
	packet->product_version = nullable_string(options->ProductVersion);

	emulator_client::get_instance()->send_packet(packet);
	PLOGI.printf("EOS_Initialize handled");

	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_ENetworkStatus)
DummyEOS_Platform_GetNetworkStatus(EOS_HPlatform handle) {
	return EOS_NS_Online;
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_Platform_SetApplicationStatus(EOS_HPlatform handle, int newStatus) {
	PLOG_INFO.printf("EOS_Platform_SetApplicationStatus called: newStatus=%d", newStatus);
	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_Platform_SetNetworkStatus(EOS_HPlatform handle, EOS_ENetworkStatus newStatus) {
	PLOG_INFO.printf("EOS_Platform_SetNetworkStatus called: newStatus=%d", newStatus);
	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_Logging_SetCallback(void* callback) {
	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_Logging_SetLogLevel(int category, int level) {
	return EOS_Success;
}

EOS_DECLARE_FUNC(EOS_EResult)
DummyEOS_ProductUserId_ToString(EOS_ProductUserId account_id, char* out_buffer, int32_t* in_out_buffer_length) {
	auto request = std::make_shared<id2string_request>();
	request->user_id = account_id;

	auto response = emulator_client::get_instance()->send_request<id2string_response>(request);
	auto buffer = response->buffer;
	auto buffer_size = response->buffer_size;
	if (buffer != nullptr) {
		ZeroMemory(out_buffer, *in_out_buffer_length);
		memcpy(out_buffer, buffer.c_str(), buffer_size + 1);
	}
	*in_out_buffer_length = buffer_size;
	PLOGI.printf("Writing: ProductUserId=%s len=%d", buffer.c_str(), buffer_size);

	return response->result;
}

EOS_DECLARE_FUNC(bool)
DummyEOS_EResult_IsOperationComplete(EOS_EResult result) {
	return true;
}
