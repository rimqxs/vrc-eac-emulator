#include <Windows.h>
#include <plog/Log.h>

#include <cstdio>

#include "bootstrapper.h"
#include "common/constants.h"
#include "common/utils.h"
#include "forwarding/forwarder.h"
#include "json.hpp"

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	forwarder::setup();
	bool isRunningOnGameProcess = GetModuleHandleA(GAME_HANDLE_NAME) != nullptr;
	if (fdwReason != DLL_PROCESS_ATTACH || !isRunningOnGameProcess) {
		return TRUE;
	}

	utils::init_logger(false);
	PLOGI.printf("Console Initialized");
	std::optional<std::string> config = utils::read_file("config.json");
	if (!config.has_value()) {
		nlohmann::json json;
		json["tcp"] = 7777;
		json["http"] = 7778;
		utils::write_file("config.json", json.dump(4));

		printf("\n\r\n\r");
		printf("+========================================================+\n\r");
		printf("|        Configuration file has been generated!          |\n\r");
		printf("| Edit the config.json file and restart the application. |\n\r");
		printf("+========================================================+\n\r");
		system("pause");
		exit(1);
	}

	nlohmann::json json = nlohmann::json::parse(config.value());
	bootstrapper::main(json["tcp"], json["http"]);

	return TRUE;
}
