cmake_minimum_required(VERSION 3.29)
project(version)

set(CMAKE_MSVC_RUNTIME_LIBRARY "")
set_property(SOURCE forwarding/jmps.asm APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")

add_library(version SHARED
        ${includes_deps}
        dllmain.cpp

        forwarding/exports.def
        forwarding/exports.cpp
        forwarding/forwarder.cpp
        forwarding/forwarder.h
        server.cpp
        server.h
)
