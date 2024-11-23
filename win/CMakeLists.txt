cmake_minimum_required(VERSION 3.29)
project(EOSSDK-Win64-Shipping)

add_library(EOSSDK-Win64-Shipping SHARED
        ${includes_deps}
        dllmain.cpp
        client.cpp
        client.h

        exports.def
        eos/eos_general.cpp
        eos/eos_notification.cpp
        eos/eos_platform.cpp
        client_packet_handler.cpp
        client_packet_handler.h
        eos/eos_session.cpp
        ../includes/eos/eos_api.h
        ../includes/eos/eos_login_types.h
        ../includes/protocol/packets/request_login_packet.cpp
        ../includes/protocol/packets/request_login_packet.h
        ../includes/nullable_string.h
)
