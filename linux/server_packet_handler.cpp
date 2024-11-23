#include "server_packet_handler.h"

#include "server.h"
#include "eos/eos_platform.h"
#include "handlers/create_platform_handler.h"
#include "handlers/request_login_handler.h"

#include "protocol/packets/handshake_packet.h"
#include "protocol/packets/c2s/create_platform_packet.h"
#include "protocol/packets/c2s/request_login_packet.h"

void server_packet_handler::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGI.printf("Handshake packet: timestamp=%lld",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
        server::send_packet(packet);
    } else if (packet->get_id() == REQUEST_LOGIN_PACKET_ID) {
    	request_login_handler::handle(packet);
	} else if (packet->get_id() == CREATE_PLATFORM_PACKET_ID) {
		create_platform_handler::handle(packet);
	}
}
