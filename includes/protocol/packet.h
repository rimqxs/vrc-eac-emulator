#pragma once

#include "packet_id.h"
#include "protocol/stream/write_stream.h"
#include "protocol/stream/read_stream.h"

class packet {
public:
    virtual ~packet() = default;

    virtual void encode(write_stream& stream) = 0;

    virtual void decode(read_stream& stream) = 0;

    virtual unsigned char get_id() = 0;
};
