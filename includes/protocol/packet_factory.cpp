#include "packet_factory.h"

#include "packets/begin_session_packet.h"
#include "packets/handshake_packet.h"
#include "packets/create_platform_packet.h"
#include "packets/initialize_eos_packet.h"

std::shared_ptr<packet> packet_factory::create_packet(const unsigned char id) {
    switch (id) {
        case HANDSHAKE_PACKET_ID:
            GENERATE_PACKET(handshake_packet);
    	case CREATE_PLATFORM_PACKET_ID:
    		GENERATE_PACKET(create_platform_packet);
    	case INITIALIZE_EOS_PACKET_ID:
    		GENERATE_PACKET(initialize_eos_packet);
    	case BEGIN_SESSION_PACKET_ID:
    		GENERATE_PACKET(begin_session_packet);
        default:
            return nullptr;
    }
}
