#include "http_server.h"

#include <httplib.h>
#include <common/api/session_factory.h>
#include <common/constants.h>
#include <json.hpp>

#include "../api/api_handler_registry.h"

void http_server::init() {
	httplib::Server server;
	server.Post("/task", [](const httplib::Request& req, httplib::Response& res) {
		PLOGI.printf("[HTTP] Request received: %s", req.body.c_str());
		nlohmann::json json = nlohmann::json::parse(req.body);
		auto request = session_factory::create_request(json["id"]);
		if (request == nullptr) {
			PLOGF.printf("Invalid request id: %s", json["id"].get<std::string>().c_str());
			res.status = 500; // Internal server error
			return;
		}
		request->deserialize(json);

		auto handler = api_handler_registry::get_handler_by_id(request->get_id());
		if (handler == nullptr) {
			return;
		}
		auto response = handler(request);

		nlohmann::json output_json;
		response->serialize(output_json);

		res.set_content(output_json.dump(), "text/plain");
		res.status = 200;
	});

	server.listen("0.0.0.0", port);
}

void http_server::run(int port) {
	http_server::port = port;
	std::thread(init).detach();
}
