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
        ../includes/api/request.h
        ../includes/api/response.h
        ../includes/api/requests/id2string_request.cpp
        ../includes/api/requests/id2string_request.h
        ../includes/api/response/id2string_response.cpp
        ../includes/api/response/id2string_response.h
        ../includes/api/json_helper.h
        ../includes/api/session_id.h
        ../includes/api/session_factory.h
)
