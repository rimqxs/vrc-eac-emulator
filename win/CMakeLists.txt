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
)
