#pragma once

#include "protocol/packet.h"

class handshake_packet : public packet {
public:
    void encode(write_stream& stream) override;

    void decode(read_stream& stream) override;

    unsigned char get_id() override;
};
