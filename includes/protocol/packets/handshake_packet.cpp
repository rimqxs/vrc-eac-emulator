#include "handshake_packet.h"

void handshake_packet::encode(write_stream &stream) {
    stream.write_as<time_t>(timestamp);
}

void handshake_packet::decode(read_stream &stream) {
    timestamp = stream.read_as<time_t>();
}

std::string handshake_packet::get_name() {
    return "handshake";
}

unsigned char handshake_packet::get_id() {
    return HANDSHAKE_PACKET_ID;
}
