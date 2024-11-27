#pragma once
#include "eos_api.h"

#pragma pack(push, 8)

struct EOS_AntiCheatClient_BeginSessionOptions {
	int32_t ApiVersion;
	EOS_ProductUserId LocalUserId;
	EOS_EAntiCheatClientMode Mode;
};

#pragma pack(pop)
