#include "receive_message_handler.h"

#include "common/protocol/packets/receive_message_packet.h"

#include "base64.hpp"
#include "../../eos/eos_anticheat.h"
#include "../../eos/eos_platform.h"

void receive_message_handler::handle(std::shared_ptr<packet> packet) {
	auto receive_message = std::dynamic_pointer_cast<receive_message_packet>(packet);

	static auto anticheat_interface = eos_platform::get_anticheat_client_interface();

	auto decoded = base64::decode_into<std::vector<char>>(receive_message->base64_message.c_str());
	if (decoded.size() != receive_message->data_length_bytes) {
		PLOGE.printf("Decoded message size does not match message data size: %d != %d", decoded.size(), receive_message->data_length_bytes);
		return;
	}

	EOS_AntiCheatClient_ReceiveMessageFromServerOptions options{};
	options.ApiVersion = receive_message->api_version;
	options.Data = decoded.data();
	options.DataLengthBytes = receive_message->data_length_bytes;
	eos_anticheat::receive_message_from_server(anticheat_interface, options);
	PLOGD.printf("receive_message_handler handled");
}
