cmake_minimum_required(VERSION 3.29)
project(version)

add_library(version SHARED
        ${includes_deps}
        dllmain.cpp

        server.cpp
        server.h
        server_packet_handler.cpp
        server_packet_handler.h

        forwarding/exports.def
        forwarding/exports.cpp
        forwarding/forwarder.cpp
        forwarding/forwarder.h
        eos/eos_platform.h
        eos/eos_platform.cpp
        eos/eos_utils.h
        handlers/create_platform_handler.cpp
        handlers/create_platform_handler.h
        handlers/request_login_handler.cpp
        handlers/request_login_handler.h
)
