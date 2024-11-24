#include "client_packet_processor.h"

#include "eos/eos.h"
#include "protocol/packets/handshake_packet.h"
#include "protocol/packets/s2c/response_id2string_packet.h"

void client_packet_processor::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGD.printf("Session successfully created: timestamp=%lld",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
    } else if (packet->get_id() == RESPONSE_LOGIN_PACKET_ID) {
	    eos::handle_response_login(std::static_pointer_cast<response_login_packet>(packet));
    } else if (packet->get_id() == RESPONSE_ID2STRING_PACKET_ID) {
    	auto response_id2string = std::static_pointer_cast<response_id2string_packet>(packet);
    	PLOGD.printf("parsed userId to str: %d", response_id2string->session_id);
	    eos::submit_id2string_result(response_id2string->session_id, response_id2string->result, response_id2string->buffer, response_id2string->buffer_size);
    }
}
