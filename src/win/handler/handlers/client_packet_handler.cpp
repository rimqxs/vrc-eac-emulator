#include "client_packet_handler.h"

#include "base64.hpp"
#include "common/protocol/packet_id.h"
#include "common/protocol/packets/handshake_packet.h"
#include "common/protocol/packets/notify_message_to_server_packet.h"
#include "plog/Log.h"

client_packet_handler::client_packet_handler(packet_sender& sender) : sender(sender) {
	registry.register_handler(HANDSHAKE_PACKET_ID, std::bind(&client_packet_handler::handle_handshake, this, std::placeholders::_1));
	registry.register_handler(NOTIFY_MESSAGE_TO_SERVER_PACKET_ID, std::bind(&client_packet_handler::handle_notify_msg_to_server, this, std::placeholders::_1));
}

void client_packet_handler::on_connected() {
	PLOGI.printf("Sending handshake packet to the server");
	auto packet = std::make_shared<handshake_packet>();
	packet->timestamp = std::time(nullptr);
	send_packet(packet);
}

handler_registry& client_packet_handler::get_handler_registry() {
	return registry;
}

void client_packet_handler::add_notify_message_to_server(notify_message_to_server_callback callback) {
	notify_message_to_server_callbacks.push_back(callback);
}

/////////////////////// handlers //////////////////////

void client_packet_handler::handle_handshake(std::shared_ptr<packet> packet) {
	PLOGD.printf("Session successfully created: timestamp=%lld", std::static_pointer_cast<handshake_packet>(packet)->timestamp);
}

void client_packet_handler::handle_notify_msg_to_server(std::shared_ptr<packet> packet) {
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

///////////////////////////////////////////////////////

void client_packet_handler::send_packet(std::shared_ptr<packet> packet) {
	sender.send_packet(packet);
}
