#include "request_login_handler.h"

#include "../../server.h"
#include "../../eos/eos_platform.h"
#include "protocol/packets/c2s/request_login_packet.h"
#include "protocol/packets/s2c/response_login_packet.h"

void EOS_CALL request_login_callback(const EOS_Connect_LoginCallbackInfo* data) {
	if (data->ResultCode == EOS_Success) {
		PLOGI.printf("Login successful: %lld", data->LocalUserId);
	} else {
		PLOGE.printf("Login failed: %d", data->ResultCode);
	}

	auto packet = std::make_shared<response_login_packet>();
	packet->session_id = *static_cast<int*>(data->ClientData);
	packet->result_code = data->ResultCode;
	packet->local_user_id = data->LocalUserId;
	packet->continuance_token = data->ContinuanceToken;
	server::send_packet(packet);

	free(data->ClientData);
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
	auto data = static_cast<int*>(malloc(sizeof(int)));
	*data = request_login->session_id;
	if (connect_interface != 0) {
		eos_platform::connect_login(connect_interface, options, data, &request_login_callback);
	}
}
