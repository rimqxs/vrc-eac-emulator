#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shlwapi.h>

#include <plog/Init.h>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "server.h"
#include "utils.h"
#include "forwarding/forwarder.h"

void init() {
    utils::createConsole();
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender);
    PLOGD.printf("Console initialized");

    if (LoadLibraryA(".\\VRChat_Data\\Plugins\\x86_64\\EOSSDK-Win64-Shipping.dll") == nullptr) {
        PLOGF.printf("Failed to perform LoadLibraryA EOSSDK-Win64-Shipping.dll!");
        return;
    }
    PLOGD.printf("EOSSDK-Win64-Shipping.dll Loaded");

    server::run();
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
    forwarder::setup();
    if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA("vrchat.exe") != nullptr) {
        init();

        PLOGW.printf("To close this process, just press enter key to exit!");
        getchar();
        exit(-1);
    }

    return TRUE;
}
