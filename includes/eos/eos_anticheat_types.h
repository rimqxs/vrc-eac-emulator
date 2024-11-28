#pragma once
#include "eos_api.h"

#pragma pack(push, 8)

struct EOS_AntiCheatClient_BeginSessionOptions {
	int32_t ApiVersion;
	EOS_ProductUserId LocalUserId;
	EOS_EAntiCheatClientMode Mode;
};

struct EOS_AntiCheatClient_AddNotifyMessageToServerOptions {
	int32_t ApiVersion;
};

struct EOS_AntiCheatClient_OnMessageToServerCallbackInfo {
	void* ClientData;
	const void* MessageData;
	uint32_t MessageDataSizeBytes;
};

struct EOS_AntiCheatClient_ReceiveMessageFromServerOptions {
	int32_t ApiVersion;
	uint32_t DataLengthBytes;
	const void* Data;
};

EOS_DECLARE_CALLBACK(EOS_AntiCheatClient_OnMessageToServerCallback, const EOS_AntiCheatClient_OnMessageToServerCallbackInfo*);

#pragma pack(pop)
