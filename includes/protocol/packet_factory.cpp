#include "packet_factory.h"

#include "packets/handshake_packet.h"

std::shared_ptr<packet> packet_factory::create_packet(unsigned char id) {
    switch (id) {
        case HANDSHAKE_PACKET_ID:
            CREATE_PKT(handshake_packet);
    }

    return nullptr;
}
