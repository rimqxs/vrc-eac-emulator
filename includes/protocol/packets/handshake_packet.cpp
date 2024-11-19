#include "handshake_packet.h"

void handshake_packet::encode(write_stream &stream) {
}

void handshake_packet::decode(read_stream &stream) {
}

unsigned char handshake_packet::get_id() {
    return HANDSHAKE_PACKET_ID;
}
