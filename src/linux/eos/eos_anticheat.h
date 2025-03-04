#pragma once

#include "common/eos/eos_anticheat_types.h"

class eos_anticheat {
public:
	static EOS_EResult begin_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_BeginSessionOptions const& options);

	static EOS_EResult end_session(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_EndSessionOptions const& options);

	static EOS_NotificationId add_notify_message_to_server(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_AddNotifyMessageToServerOptions const& options, void* client_data, EOS_AntiCheatClient_OnMessageToServerCallback notification_fn);

	static void receive_message_from_server(EOS_HAntiCheatClient handle, EOS_AntiCheatClient_ReceiveMessageFromServerOptions const& options);
};
