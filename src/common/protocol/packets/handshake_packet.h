#pragma once

#include <common/protocol/packet.h>
#include <common/protocol/stream/read_stream.h>
#include <common/protocol/stream/write_stream.h>
#include <ctime>

class handshake_packet : public packet {
public:
    time_t timestamp = 0;

    void encode(write_stream& stream) override;

    void decode(read_stream& stream) override;

    std::string get_name() override;

    unsigned char get_id() override;
};
