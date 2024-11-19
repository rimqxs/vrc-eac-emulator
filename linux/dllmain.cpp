#include <Windows.h>

#include <shlwapi.h>

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "constants.h"
#include "server.h"
#include "utils.h"
#include "forwarding/forwarder.h"

void init() {
    utils::initLogger();
    PLOGI.printf("Console initialized");

    if (LoadLibraryA(EOS_SDK_PATH) == nullptr) {
        PLOGF.printf("Failed to perform LoadLibraryA EOSSDK-Win64-Shipping.dll!");
        return;
    }
    PLOGD.printf("EOSSDK-Win64-Shipping.dll Loaded");

    server::run();
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
    forwarder::setup();
    if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA(GAME_HANDLE_NAME) != nullptr) {
        init();

        PLOGW.printf("To close this process, just press enter key to exit!");
        getchar();
        exit(-1);
    }

    return TRUE;
}
