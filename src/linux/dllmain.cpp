#include <Windows.h>
#include <plog/Log.h>

#include <cstdio>

#include "bootstrapper.h"
#include "common/constants.h"
#include "common/exception_handler.hpp"
#include "common/utils.h"
#include "forwarding/forwarder.h"
#include "json.hpp"

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	forwarder::setup();

	bool isRunningOnGameProcess = GetModuleHandleA(GAME_HANDLE_NAME) != nullptr;
	if (fdwReason != DLL_PROCESS_ATTACH || !isRunningOnGameProcess) {
		return TRUE;
	}
	exception_handler::init();

	utils::create_console();
	printf("Console Initialized\n");
	std::optional<std::string> config = utils::read_file("config.json");
	if (!config.has_value()) {
		nlohmann::json json;
		json["tcp"] = 7777;
		json["http"] = 7778;
		json["logger"] = true;
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
	bool use_logger = json["logger"];
	utils::init_logger(false, use_logger ? plog::verbose : plog::none);
	bootstrapper::main(json["tcp"], json["http"]);

	return TRUE;
}
