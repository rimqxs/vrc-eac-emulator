#include <eos/eos_api.h>
#include <eos/eos_login_types.h>

#include "eos.h"
#include "../client.h"
#include "protocol/packet_factory.h"
#include "protocol/packets/c2s/request_login_packet.h"

static inline int session_id = 1000;
EOS_DECLARE_FUNC(void) DummyEOS_Connect_Login(EOS_HConnect handle, const EOS_Connect_LoginOptions* options, void* client_data, const EOS_Connect_OnLoginCallback completion_delegate) {
	auto packet = std::make_shared<request_login_packet>();
	packet->session_id = session_id++;
	packet->api_version = options->ApiVersion;

	packet->has_credentials = options->Credentials != nullptr;
	if (options->Credentials != nullptr) {
		packet->credentials.ApiVersion = options->Credentials->ApiVersion;
		packet->credentials.Token = nullable_string(options->Credentials->Token);
		packet->credentials.Type = options->Credentials->Type;
	}

	packet->has_login_info = options->UserLoginInfo != nullptr;
	if (options->UserLoginInfo != nullptr) {
		packet->user_login_info.ApiVersion = options->UserLoginInfo->ApiVersion;
		packet->user_login_info.DisplayName = nullable_string(options->UserLoginInfo->DisplayName);
		packet->user_login_info.NsaIdToken = nullable_string(options->UserLoginInfo->NsaIdToken);
	}

	PLOGI.printf("Requesting login to proxy");
	eos::register_connect_callback(packet->session_id, std::make_tuple(client_data, completion_delegate));
	client::send_packet(packet);
}
