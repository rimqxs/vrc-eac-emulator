#include "handshake_packet_handler.h"

#include "../../server.h"
#include "protocol/packets/handshake_packet.h"

void handshake_packet_handler::handle(std::shared_ptr<packet> packet) {
	PLOGI.printf("Handshake packet: timestamp=%lld",
		 std::static_pointer_cast<handshake_packet>(packet)->timestamp);
	server::send_packet(packet);
}
