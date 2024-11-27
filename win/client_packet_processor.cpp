#include "client_packet_processor.h"

#include "protocol/packets/handshake_packet.h"

void client_packet_processor::handle(std::shared_ptr<packet> packet) {
    if (packet->get_id() == HANDSHAKE_PACKET_ID) {
        PLOGD.printf("Session successfully created: timestamp=%lld",
                     std::static_pointer_cast<handshake_packet>(packet)->timestamp);
    }
}
