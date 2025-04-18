#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <plog/Log.h>

#include "common/constants.h"
#include "common/utils.h"
#include "emulator_client.h"
#include "json.hpp"

emulator_client* client;
void init() {
	utils::create_console();
	printf("Console Initialized\n");

	std::optional<std::string> config = utils::read_file("config.json");
	if (!config.has_value()) {
		nlohmann::json json;
		nlohmann::json ports_obj;
		json["ip"] = "192.168.XXX.XXX";
		ports_obj["tcp"] = 7777;
		ports_obj["http"] = 7778;
		json["ports"] = ports_obj;
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
	utils::init_logger(true, use_logger ? plog::verbose : plog::none);

	client = new emulator_client(json["ip"], json["ports"]["http"]);
	client->connect(json["ports"]["tcp"]);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	if (fdwReason == DLL_PROCESS_ATTACH && GetModuleHandleA(GAME_HANDLE_NAME) != nullptr) {
		init();
	}
	return TRUE;
}
