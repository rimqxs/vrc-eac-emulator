cmake_minimum_required(VERSION 3.29)
project(EOSSDK-Win64-Shipping)

add_library(EOSSDK-Win64-Shipping SHARED
        ${includes_deps}

        ../common/constants.h

        dllmain.cpp
        client.cpp
        client.h
        exports.def

        eos_impl/eos_general_impl.cpp
        eos_impl/eos_notification_impl.cpp
        eos_impl/eos_platform_impl.cpp
        eos_impl/eos_session_impl.cpp
        eos_impl/eos_anticheat_impl.cpp
        
        client_packet_handler.cpp
        client_packet_handler.h
)
target_link_libraries(EOSSDK-Win64-Shipping minhook)
target_include_directories(EOSSDK-Win64-Shipping PUBLIC ${plog_SOURCE_DIR}/include)