#include "end_session_handler.h"

#include "common/eos/eos_anticheat_types.h"
#include "common/protocol/packets/end_session_packet.h"

#include "../../eos/eos_anticheat.h"
#include "../../eos/eos_platform.h"

void end_session_handler::handle(std::shared_ptr<packet> packet) {
	auto end_session = std::static_pointer_cast<end_session_packet>(packet);

	static auto anticheat_interface = eos_platform::get_anticheat_client_interface();
	if (anticheat_interface == NULL) {
		PLOGF.printf("Could not retrieve anticheat client interface");
		return;
	}

	EOS_AntiCheatClient_EndSessionOptions options{};
	options.ApiVersion = end_session->options.ApiVersion;
	if (eos_anticheat::end_session(anticheat_interface, options) == EOS_Success) {
		PLOGI.printf("AntiCheat session successfully began");
	} else {
		PLOGE.printf("Failed to begin AntiCheat session!");
	}
}
