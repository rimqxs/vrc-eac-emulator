#pragma once

#include "protocol/packet.h"

class handshake_packet : public packet {
public:
    time_t timestamp = 0;

    void encode(write_stream& stream) override;

    void decode(read_stream& stream) override;

    std::string get_name() override;

    unsigned char get_id() override;
};
