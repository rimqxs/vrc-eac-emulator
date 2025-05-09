#include "http_server.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <common/api/session_factory.h>
#include <hv/HttpServer.h>

#include <json.hpp>
#include <thread>

#include "../api/api_handler_registry.h"

void http_server::init() {
	HttpService router;
	router.POST("/task", [](HttpRequest* req, HttpResponse* resp) {
		nlohmann::json json = nlohmann::json::parse(req->body);
		auto request = session_factory::create_request(json["id"]);
		if (request == nullptr) {
			PLOGF.printf("Invalid request id: %s", json["id"].get<std::string>().c_str());
			return resp->String(nlohmann::json({{"status", "error"}}).dump());
		}
		request->deserialize(json);

		auto handler = api_handler_registry::get_handler_by_id(request->get_id());
		if (handler == nullptr) {
			return resp->String(nlohmann::json({{"status", "error"}}).dump());
		}
		auto response = handler(request);

		nlohmann::json output_json;
		response->serialize(output_json);

		return resp->String(output_json.dump());
	});

	hv::HttpServer server(&router);
	server.setPort(port);
	server.setThreadNum(4);
	server.run();
}

void http_server::run(int port) {
	http_server::port = port;
	std::thread(init).detach();
}
