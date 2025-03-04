#include "login_handler.h"

#include <condition_variable>
#include <mutex>
#include <plog/Log.h>

#include "vlock.h"
#include "common/api/requests/login_request.h"
#include "common/api/response/login_response.h"
#include "common/eos/eos_login_types.h"

#include "../eos/eos_connect.h"
#include "../eos/eos_platform.h"

void EOS_CALL request_login_callback(const EOS_Connect_LoginCallbackInfo* data) {
	if (data->ResultCode == EOS_Success) {
		PLOGI.printf("Login successful: %lld", data->LocalUserId);
	} else {
		PLOGE.printf("Login failed: %d", data->ResultCode);
	}

	auto response = std::make_shared<login_response>();
	response->result_code = data->ResultCode;
	response->local_user_id = data->LocalUserId;
	response->continuance_token = data->ContinuanceToken;

	auto lock = static_cast<vlock<std::shared_ptr<login_response>>*>(data->ClientData);
	lock->set_callback(response);
}

std::shared_ptr<response> login_handler::handle(std::shared_ptr<request> request) {
	auto request_login = std::static_pointer_cast<login_request>(request);

	std::string logText = "Processing Login:\n";
	if (request_login->has_credentials) {
		logText.append(" - Credentials\n");
		logText.append(std::format("    ApiVersion: {}\n", request_login->credentials.ApiVersion));
		logText.append(std::format("    Type: {}\n", request_login->credentials.Type));
		logText.append(std::format("    Token: {}\n", request_login->credentials.Token.c_str()));
	}
	if (request_login->has_login_info) {
		logText.append(" - Login Info\n");
		logText.append(std::format("    ApiVersion: {}\n", request_login->user_login_info.ApiVersion));
		logText.append(std::format("    DisplayName: {}\n", request_login->user_login_info.DisplayName.c_str()));
		logText.append(std::format("    NsaIdToken: {}", request_login->user_login_info.NsaIdToken.c_str()));
	}
	PLOGI.printf("%s", logText.c_str());

	EOS_Connect_LoginOptions options{};
	options.ApiVersion = request_login->api_version;

	EOS_Connect_Credentials credentials{};
	options.Credentials = nullptr;
	if (request_login->has_credentials) {
		credentials.ApiVersion = request_login->credentials.ApiVersion;
		credentials.Token = request_login->credentials.Token.c_str();
		credentials.Type = request_login->credentials.Type;
		options.Credentials = &credentials;
	}

	EOS_Connect_UserLoginInfo user_login_info{};
	options.UserLoginInfo = nullptr;
	if (request_login->has_login_info) {
		user_login_info.ApiVersion = request_login->user_login_info.ApiVersion;
		user_login_info.DisplayName = request_login->user_login_info.DisplayName.c_str();
		user_login_info.NsaIdToken = request_login->user_login_info.NsaIdToken.c_str();
		options.UserLoginInfo = &user_login_info;
	}

	vlock<std::shared_ptr<login_response>> lock;
	EOS_HConnect connect_interface = eos_platform::get_connect_interface();
	if (connect_interface != 0) {
		eos_connect::login(connect_interface, options, &lock, &request_login_callback);
	}

	return lock.wait();
}