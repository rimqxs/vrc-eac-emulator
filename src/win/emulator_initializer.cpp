#include "emulator_initializer.h"

#include <optional>
#include <string>

#include "common/utils.h"
#include "win/emulator_client.h"

emulator_client* client;
EmulatorStauts emulator_initializer::init() {
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
		return EmulatorStauts::REQUIRED_CLOSE;
	}

	nlohmann::json json = nlohmann::json::parse(config.value());
	bool use_logger = json["logger"];
	utils::init_logger(true, use_logger ? plog::verbose : plog::none);

	client = new emulator_client(json["ip"], json["ports"]["http"]);
	client->connect(json["ports"]["tcp"]);
	return EmulatorStauts::OK;
}
