#include "begin_session_handler.h"

#include "../../eos/eos_anticheat.h"
#include "../../eos/eos_platform.h"
#include "protocol/packets/begin_session_packet.h"

void begin_session_handler::handle(std::shared_ptr<packet> packet) {
	auto begin_session = std::static_pointer_cast<begin_session_packet>(packet);

	static auto anticheat_interface = eos_platform::get_anticheat_client_interface();
	if (anticheat_interface == NULL) {
		PLOGF.printf("Could not retrieve anticheat client interface");
		return;
	}

	EOS_AntiCheatClient_BeginSessionOptions options{};
	options.ApiVersion = begin_session->api_version;
	options.LocalUserId = begin_session->user_id;
	options.Mode = begin_session->mode;

	if (eos_anticheat::begin_session(anticheat_interface, options) == EOS_Success) {
		PLOGI.printf("AntiCheat session successfully began");
	} else {
		PLOGE.printf("Failed to begin AntiCheat session!");
	}
}
