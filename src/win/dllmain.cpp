#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <plog/Log.h>

#include "common/constants.h"
#include "common/exception_handler.hpp"
#include "common/utils.h"
#include "emulator_client.h"
#include "json.hpp"

void init() {
	exception_handler::init();
	utils::create_console();
	printf("Console Initialized\n");
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA(GAME_HANDLE_NAME) != nullptr) {
		init();
	}
	return TRUE;
}
