#include "packet_factory.h"

#include "packets/handshake_packet.h"
#include "packets/request_login_packet.h"

std::shared_ptr<packet> packet_factory::create_packet(const unsigned char id) {
    switch (id) {
        case HANDSHAKE_PACKET_ID:
            GENERATE_PACKET(handshake_packet);
    	case REQUEST_LOGIN_PACKET_ID:
    		GENERATE_PACKET(request_login_packet);
        default:
            return nullptr;
    }
}
