cmake_minimum_required(VERSION 3.29)
project(EOSSDK-Win64-Shipping)

add_library(EOSSDK-Win64-Shipping SHARED
        ${includes_deps}
        dllmain.cpp
        client.cpp
        client.h

        exports.def
        eos/eos_api.h
        eos/eos_general.cpp
        eos/eos_notification.cpp
        eos/eos_platform.cpp
        ../includes/protocol/packet.h
        ../includes/protocol/packets/handshake_packet.cpp
        ../includes/protocol/packets/handshake_packet.h
        ../includes/protocol/packet_id.h
        ../includes/protocol/stream/read_stream.h
        ../includes/protocol/packet_codec.cpp
        ../includes/protocol/packet_codec.h
        ../includes/protocol/packet_factory.cpp
        ../includes/protocol/packet_factory.h
        ../includes/protocol/stream/write_stream.h
        ../includes/protocol/stream/buffer.h
)
