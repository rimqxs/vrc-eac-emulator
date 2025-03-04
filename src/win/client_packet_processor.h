#pragma once
#include <memory>

#include "common/eos/eos_anticheat_types.h"
#include "common/protocol/packet.h"

struct notify_message_to_server_callback {
	EOS_AntiCheatClient_AddNotifyMessageToServerOptions options;
	void* client_data;
	EOS_AntiCheatClient_OnMessageToServerCallback notification_fn;
};

class client_packet_processor {
	static inline std::vector<notify_message_to_server_callback> notify_message_to_server_callbacks;
public:
    static void handle(std::shared_ptr<packet> packet);

	static void add_notify_message_to_server(notify_message_to_server_callback callback);
};
