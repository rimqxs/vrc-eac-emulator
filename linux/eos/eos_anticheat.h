#pragma once
#include "eos/eos_anticheat_types.h"

class eos_anticheat {
public:
	static EOS_EResult begin_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_BeginSessionOptions const& options);
};
