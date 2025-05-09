#include "bootstrapper.h"

#include <MinHook.h>
#include <common/constants.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Log.h>
#include <shlwapi.h>

#include "api/api_handler_registry.h"
#include "eos/eos.h"
#include "eos/eos_platform.h"
#include "handlers/handler_registry.h"
#include "servers/http_server.h"
#include "servers/websocket_server.h"

int bootstrapper::Dummy_WinMain() {
	handler_registry::init();
	api_handler_registry::init();

	websocket_server::launch(tcp_port);
	http_server::run(http_port);

	while (true) {
		Sleep(1000 / 30);  // emulate 30 fps

		websocket_server::tick();
		if (eos::is_eos_initialized() && eos_platform::is_platform_created()) {
			eos_platform::tick();
		}
	}
}

void bootstrapper::hook_winmain() {
	MH_Initialize();

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
}

void bootstrapper::main(int tcp_port, int http_port) {
	bootstrapper::tcp_port = tcp_port;
	bootstrapper::http_port = http_port;

	if (LoadLibraryA(EOS_SDK_PATH) == nullptr) {
		PLOGF.printf("Failed to perform LoadLibraryA EOSSDK-Win64-Shipping.dll!");
		return;
	}
	PLOGD.printf("EOSSDK-Win64-Shipping.dll Loaded");

	hook_winmain();
}
