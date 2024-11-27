#include "eos_anticheat.h"

#include "eos_utils.h"

EOS_EResult eos_anticheat::begin_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_BeginSessionOptions const& options) {
	typedef EOS_EResult(EOS_CALL* EOS_AntiCheatClient_BeginSession)(EOS_HAntiCheatClient, const EOS_AntiCheatClient_BeginSessionOptions*);
	static auto eos_anticheat_client_begin_session = reinterpret_cast<EOS_AntiCheatClient_BeginSession>(
		eos_utils::get_eos_proc_addr("EOS_AntiCheatClient_BeginSession"));
	if (!eos_anticheat_client_begin_session) {
		PLOGF.printf("Could not resolve EOS_AntiCheatClient_BeginSession");
		return 0;
	}

	return eos_anticheat_client_begin_session(handle, &options);
}
