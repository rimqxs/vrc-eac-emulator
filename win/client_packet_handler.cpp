#include "client_packet_handler.h"

#include "protocol/packets/handshake_packet.h"


void client_packet_handler::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGD.printf("Session successfully created: timestamp=%ll",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
    }
}
