#include "request_login_handler.h"

#include "../../eos/eos_platform.h"
#include "protocol/packets/c2s/request_login_packet.h"

void EOS_CALL request_login_callback(const EOS_Connect_LoginCallbackInfo* data) {
	PLOGI.printf("Login Callback: ResultCode=%d, LocalUserId=%d", data->ResultCode, data->LocalUserId);
}

void request_login_handler::handle(std::shared_ptr<packet> packet) {
	auto request_login = std::static_pointer_cast<request_login_packet>(packet);

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

	EOS_HConnect connect_interface = eos_platform::get_connect_interface();
	if (connect_interface != 0) {
		eos_platform::connect_login(connect_interface, options, &request_login_callback);
	}
}
