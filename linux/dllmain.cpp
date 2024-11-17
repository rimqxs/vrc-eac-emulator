#include <Windows.h>
#include <shlwapi.h>

#include <plog/Init.h>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "server.h"
#include "Utils.h"
#include "forwarding/forwarder.h"

server server;
void init() {
    Utils::createConsole();
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);
    PLOGD.printf("Console initialized");

    if (LoadLibraryA(".\\VRChat_Data\\Plugins\\x86_64\\EOSSDK-Win64-Shipping.dll") == nullptr) {
        PLOGF.printf("Failed to perform LoadLibraryA EOSSDK-Win64-Shipping.dll!");
        return;
    }
    PLOGD.printf("EOSSDK-Win64-Shipping.dll Loaded");

    server.run();
    PLOGI.printf("EOS Emulator started correctly");
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            forwarder::setup();
            if (GetModuleHandleA("vrchat.exe") != nullptr) {
                init();

                PLOGW.printf("To close this process, just press enter key to exit!");
                getchar();
                exit(-1);
            }
        break;
        default:break;
    }
    return TRUE;
}
