cmake_minimum_required(VERSION 3.29)
project(EOSSDK-Win64-Shipping)

add_library(EOSSDK-Win64-Shipping SHARED
        ${includes_deps}
        dllmain.cpp
        emulator_client.cpp
        emulator_client.h
        emulator_initializer.cpp
        emulator_initializer.h
        exports.def

        eos_impl/eos_general_impl.cpp
        eos_impl/eos_notification_impl.cpp
        eos_impl/eos_platform_impl.cpp
        eos_impl/eos_session_impl.cpp
        eos_impl/eos_anticheat_impl.cpp
        
        handler/handlers/client_packet_handler.cpp
        handler/handlers/client_packet_handler.h
        handler/packet_handler.h
        handler/handler_registry.cpp
        handler/handler_registry.h

        sock/packet_sender.cpp
        sock/packet_sender.h
        sock/websocket_client.cpp
        sock/websocket_client.h
)
target_link_libraries(EOSSDK-Win64-Shipping hv_static crashlog)