cmake_minimum_required(VERSION 3.29)
project(version)

add_library(version SHARED
        ${includes_deps}
        dllmain.cpp

        forwarding/exports.def
        forwarding/exports.cpp
        forwarding/forwarder.cpp
        forwarding/forwarder.h
        server.cpp
        server.h
        server_packet_handler.cpp
        server_packet_handler.h
)
