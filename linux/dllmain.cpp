#include <Windows.h>
#include <shlwapi.h>

#include <MinHook.h>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "constants.h"
#include "server.h"
#include "utils.h"
#include "eos/eos.h"
#include "eos/eos_platform.h"
#include "forwarding/forwarder.h"

int __stdcall Dummy_WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	server::run();

	PLOGW.printf("EOS Emulator has been initialized successfully! Press Enter key to close this process...");
	while (!GetAsyncKeyState(VK_RETURN)) {
		Sleep(1000 / 30); // emulate 30 fps

		server::tick();

		if (!eos::is_eos_initialized() || !eos_platform::is_platform_created()) {
			continue;
		}
		eos_platform::tick();
	}

	return 0;
}

void init() {
	utils::init_logger();
	PLOGI.printf("Console initialized");

	if (LoadLibraryA(EOS_SDK_PATH) == nullptr) {
		PLOGF.printf("Failed to perform LoadLibraryA EOSSDK-Win64-Shipping.dll!");
		return;
	}
	PLOGD.printf("EOSSDK-Win64-Shipping.dll Loaded");

	MH_Initialize();
#if HOOK_MODE==il2cpp
	HMODULE unityPlayerHandle = GetModuleHandleA("UnityPlayer.dll");
	void* unityMain = GetProcAddress(unityPlayerHandle, "UnityMain");
	PLOGD.printf("UnityPlayer.dll WinMain=%llx", unityMain);

	void* originalFunc;
	if (MH_CreateHook(unityMain, &Dummy_WinMain, &originalFunc) != MH_OK || MH_EnableHook(unityMain) != MH_OK) {
		PLOGF.printf("Failed to create hook of UnityMain");
		return;
	}
	PLOGI.printf("Created WinMain function hook");
	PLOGI.printf("Waiting for the main process...");
#endif
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	forwarder::setup();
	if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA(GAME_HANDLE_NAME) != nullptr) {
		init();
	}

	return TRUE;
}