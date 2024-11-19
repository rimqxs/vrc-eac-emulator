#pragma once

#include <memory>

#include "packet.h"
#include "stream/read_stream.h"
#include "stream/write_stream.h"

class packet_codec {
public:
    static write_stream encode(const std::shared_ptr<packet>& packet);

    static std::shared_ptr<packet> decode(read_stream& stream);
};
