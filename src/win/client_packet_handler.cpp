#include "base64.hpp"
#include "client_packet_handler.h"
#include "common/eos/eos_anticheat_types.h"
#include "common/protocol/packets/handshake_packet.h"
#include "common/protocol/packets/notify_message_to_server_packet.h"

void client_packet_handler::handle(std::shared_ptr<packet> packet) {
	if (packet->get_id() == HANDSHAKE_PACKET_ID) {
		PLOGD.printf("Session successfully created: timestamp=%lld",
					 std::static_pointer_cast<handshake_packet>(packet)->timestamp);
	} else if (packet->get_id() == NOTIFY_MESSAGE_TO_SERVER_PACKET_ID) {
		auto notify_message_to_server = std::static_pointer_cast<notify_message_to_server_packet>(packet);
		auto decoded = base64::decode_into<std::vector<char>>(notify_message_to_server->base64_message_data.c_str());
		if (decoded.size() != notify_message_to_server->message_data_size) {
			PLOGE.printf("Decoded message size does not match message data size");
			return;
		}

		for (auto& callback : notify_message_to_server_callbacks) {
			EOS_AntiCheatClient_OnMessageToServerCallbackInfo info{};
			info.ClientData = callback.client_data;
			info.MessageData = decoded.data();
			info.MessageDataSizeBytes = notify_message_to_server->message_data_size;
			callback.notification_fn(&info);
		}
	}
}

void client_packet_handler::add_notify_message_to_server(notify_message_to_server_callback callback) {
	notify_message_to_server_callbacks.push_back(callback);
}
