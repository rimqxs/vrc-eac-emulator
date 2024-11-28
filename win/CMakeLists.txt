cmake_minimum_required(VERSION 3.29)
project(EOSSDK-Win64-Shipping)

add_library(EOSSDK-Win64-Shipping SHARED
        ${includes_deps}
        dllmain.cpp
        client.cpp
        client.h

        exports.def
        eos/eos_general_impl.cpp
        eos/eos_notification_impl.cpp
        eos/eos_platform_impl.cpp
        client_packet_processor.cpp
        client_packet_processor.h
        eos/eos_session_impl.cpp
        eos/eos_anticheat_impl.cpp
        ../includes/protocol/packets/notify_message_to_server_packet.cpp
        ../includes/protocol/packets/notify_message_to_server_packet.h
        ../includes/protocol/packets/receive_message_packet.cpp
        ../includes/protocol/packets/receive_message_packet.h
)
