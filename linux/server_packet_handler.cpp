#include "server_packet_handler.h"

#include "server.h"

#include "protocol/packets/handshake_packet.h"
#include "protocol/packets/request_login_packet.h"

void server_packet_handler::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGI.printf("Handshake packet: timestamp=%lld",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
        server::send_packet(packet);
    } else if (packet->get_id() == REQUEST_LOGIN_PACKET_ID) {
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
}
