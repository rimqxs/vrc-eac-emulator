#include "server_packet_handler.h"

#include "server.h"
#include "protocol/packets/handshake_packet.h"

void client_packet_handler::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGD.printf("Sending back handshake packet: timestamp=%ll",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
        server::send_packet(packet);
    }
}
