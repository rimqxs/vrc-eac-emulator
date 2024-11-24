cmake_minimum_required(VERSION 3.29)
project(version)

add_library(version SHARED
        ${includes_deps}
        dllmain.cpp

        server.cpp
        server.h

        eos/eos_logger.h
        eos/eos_platform.h
        eos/eos_platform.cpp
        eos/eos_utils.h
        eos/eos.cpp
        eos/eos.h

        handlers/handler_registry.h
        handlers/platform/create_platform_handler.cpp
        handlers/platform/create_platform_handler.h
        handlers/platform/request_login_handler.cpp
        handlers/platform/request_login_handler.h
        handlers/common/initialize_eos_handler.cpp
        handlers/common/initialize_eos_handler.h
        handlers/common/handshake_packet_handler.cpp
        handlers/common/handshake_packet_handler.h

        forwarding/exports.def
        forwarding/exports.cpp
        forwarding/forwarder.cpp
        forwarding/forwarder.h
        handlers/common/request_id2string_handler.cpp
        handlers/common/request_id2string_handler.h
)
