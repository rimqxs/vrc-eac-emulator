#include "utils.h"
#include "../client.h"
#include "eos/eos_anticheat_types.h"
#include "eos/eos_api.h"
#include "protocol/packets/begin_session_packet.h"

EOS_DECLARE_FUNC(EOS_EResult) DummyEOS_AntiCheatClient_BeginSession(EOS_HAntiCheatClient handle, const EOS_AntiCheatClient_BeginSessionOptions* options) {
	PLOGI.printf("Beginning session with mode: %d", options->Mode);
	auto packet = std::make_shared<begin_session_packet>();
	packet->api_version = options->ApiVersion;
	packet->user_id = options->LocalUserId;
	packet->mode = options->Mode;
	client::send_packet(packet);

	utils::sleep(1000); // delaying for 1 second to make sure the packet is processed

	return EOS_Success;
}
