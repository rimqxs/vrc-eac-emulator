#include "request_login_handler.h"

#include "protocol/packets/c2s/request_login_packet.h"

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
		logText.append(std::format("    NsaIdToken: {}\n", request_login->user_login_info.NsaIdToken.c_str()));
	}
	PLOGI.printf("%s", logText.c_str());
}