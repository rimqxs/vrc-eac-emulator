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
        ../includes/api/requests/login_status_request.cpp
        ../includes/api/requests/login_status_request.h
        ../includes/api/response/login_status_response.cpp
        ../includes/api/response/login_status_response.h
        ../includes/protocol/packets/begin_session_packet.cpp
        ../includes/protocol/packets/begin_session_packet.h
        ../includes/eos/eos_anticheat_types.h
        eos/eos_anticheat_impl.cpp
)
