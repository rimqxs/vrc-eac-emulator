#pragma once

#include <memory>

#include "../handler_registry.h"
#include "../packet_handler.h"
#include "common/eos/eos_anticheat_types.h"
#include "common/protocol/packet.h"
#include "win/sock/packet_sender.h"

struct notify_message_to_server_callback {
	EOS_AntiCheatClient_AddNotifyMessageToServerOptions options;
	void* client_data;
	EOS_AntiCheatClient_OnMessageToServerCallback notification_fn;
};

class client_packet_handler : public packet_handler {
	packet_sender& sender;
	handler_registry registry;

	static inline std::vector<notify_message_to_server_callback> notify_message_to_server_callbacks;

public:
	client_packet_handler(packet_sender& sender);

	void on_connected() override;

	handler_registry& get_handler_registry() override;

	static void add_notify_message_to_server(notify_message_to_server_callback callback);

private:
	void handle_handshake(std::shared_ptr<packet> packet);

	void handle_notify_msg_to_server(std::shared_ptr<packet> packet);

	void send_packet(std::shared_ptr<packet> packet);
};
