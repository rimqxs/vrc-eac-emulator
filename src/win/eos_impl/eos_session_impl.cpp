#include "common/eos/eos_api.h"
#include "common/eos/eos_login_types.h"
#include "common/api/requests/login_request.h"
#include "common/api/requests/login_status_request.h"
#include "common/api/response/login_response.h"
#include "common/api/response/login_status_response.h"
#include "common/protocol/packet_factory.h"
#include "common/utils.h"

#include <thread>

#include "../client.h"


void login_callback(const EOS_Connect_OnLoginCallback completion_delegate, void* client_data, std::shared_ptr<login_response> response) {
	utils::sleep(400); // delay

	EOS_Connect_LoginCallbackInfo info{};
	info.ResultCode = response->result_code;
	info.ClientData = client_data;
	info.LocalUserId = response->local_user_id;
	info.ContinuanceToken = response->continuance_token;
	completion_delegate(&info);
	PLOGD.printf("Logged in successfully: user_id=%d", info.LocalUserId);
}

EOS_DECLARE_FUNC(void) DummyEOS_Connect_Login(EOS_HConnect handle, const EOS_Connect_LoginOptions* options, void* client_data, const EOS_Connect_OnLoginCallback completion_delegate) {
	auto request = std::make_shared<login_request>();
	request->api_version = options->ApiVersion;

	request->has_credentials = options->Credentials != nullptr;
	if (options->Credentials != nullptr) {
		request->credentials.ApiVersion = options->Credentials->ApiVersion;
		request->credentials.Token = nullable_string(options->Credentials->Token);
		request->credentials.Type = options->Credentials->Type;
	}

	request->has_login_info = options->UserLoginInfo != nullptr;
	if (options->UserLoginInfo != nullptr) {
		request->user_login_info.ApiVersion = options->UserLoginInfo->ApiVersion;
		request->user_login_info.DisplayName = nullable_string(options->UserLoginInfo->DisplayName);
		request->user_login_info.NsaIdToken = nullable_string(options->UserLoginInfo->NsaIdToken);
	}

	PLOGI.printf("Requesting login to proxy");
	auto response = client::request<login_response>(request);
	std::thread(login_callback, completion_delegate, client_data, response).detach();
}

EOS_DECLARE_FUNC(EOS_ELoginStatus) DummyEOS_Connect_GetLoginStatus(EOS_HConnect Handle, EOS_ProductUserId LocalUserId) {
	auto request = std::make_shared<login_status_request>();
	request->user_id = LocalUserId;

	auto response = client::request<login_status_response>(request);
	return response->status;
}
