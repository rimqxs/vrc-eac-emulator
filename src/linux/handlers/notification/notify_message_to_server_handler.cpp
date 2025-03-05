#include "notify_message_to_server_handler.h"

#include "common/eos/eos_anticheat_types.h"
#include "common/protocol/packets/notify_message_to_server_packet.h"
#include "base64.hpp"

#include "../../eos/eos_anticheat.h"
#include "../../eos/eos_platform.h"
#include "../../servers/socket_server.h"

void notify_message_to_server_callback(const EOS_AntiCheatClient_OnMessageToServerCallbackInfo* data) {
	std::vector<char> message_bytes;
	for (int i = 0; i < data->MessageDataSizeBytes; i++) {
		message_bytes.push_back(static_cast<const char*>(data->MessageData)[i]);
	}
	auto message_base64 = base64::encode_into<std::string>(message_bytes.begin(), message_bytes.end());

	auto packet = std::make_shared<notify_message_to_server_packet>();
	packet->require_bind = false;
	packet->base64_message_data = nullable_string(message_base64);
	packet->message_data_size = data->MessageDataSizeBytes;
	socket_server::send_packet(packet);
}

void notify_message_to_server_handler::handle(std::shared_ptr<packet> packet) {
	auto notify_message_to_server = std::static_pointer_cast<notify_message_to_server_packet>(packet);

	static auto anticheat_interface = eos_platform::get_anticheat_client_interface();

	EOS_AntiCheatClient_AddNotifyMessageToServerOptions options{};
	options.ApiVersion = notify_message_to_server->options.ApiVersion;
	eos_anticheat::add_notify_message_to_server(anticheat_interface, options, nullptr, &notify_message_to_server_callback);
	PLOGI.printf("AntiCheatClient_AddNotifyMessageToServer bound");
}
