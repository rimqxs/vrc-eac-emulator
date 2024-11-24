#include "request_id2string_handler.h"

#include "../../server.h"
#include "../../eos/eos.h"
#include "protocol/packets/c2s/request_id2string_packet.h"
#include "protocol/packets/s2c/response_id2string_packet.h"

#define EOS_PRODUCTUSERID_MAX_LENGTH 32

void request_id2string_handler::handle(std::shared_ptr<packet> packet) {
	auto request_id2string = std::static_pointer_cast<request_id2string_packet>(packet);

	char buffer[EOS_PRODUCTUSERID_MAX_LENGTH+1];
	int32_t buffer_length = sizeof(buffer);
	ZeroMemory(buffer, sizeof(buffer));
	EOS_EResult result = eos::product_user_id_to_string(request_id2string->user_id, buffer, &buffer_length);
	if (result != EOS_Success) {
		PLOGE.printf("Failed to parse userId to str: %d, length=%d", result, buffer_length);
	} else {
		PLOGD.printf("parsed userId to str: %s", buffer);
	}

	auto response_packet = std::make_shared<response_id2string_packet>();
	response_packet->session_id = request_id2string->session_id;
	response_packet->result = result;
	response_packet->buffer = nullable_string(buffer);
	response_packet->buffer_size = buffer_length;
	server::send_packet(response_packet);
}
