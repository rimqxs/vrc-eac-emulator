#include "emulator_client.h"

#include <memory>

#include "common/api/session_factory.h"
#include "handler/handlers/client_packet_handler.h"
#include "httplib.h"

emulator_client::emulator_client(std::string address, int http_port) : address(address), http_port(http_port), client(std::make_shared<client_packet_handler>(sender)) {
	instance = this;
}

void emulator_client::connect(int tcp_port) {
	client.run(address, tcp_port);
	sender.start(client.get_socket());
}

void emulator_client::send_packet(std::shared_ptr<packet> packet) {
	sender.send_packet(packet);
}

emulator_client* emulator_client::get_instance() {
	return instance;
}

std::shared_ptr<response> emulator_client::_request(std::shared_ptr<request> const& request) {
	httplib::Client client(std::format("http://{}:{}", address, http_port));
	nlohmann::json serialized;
	request->serialize(serialized);
	auto res = client.Post("/task", serialized.dump(), "application/json");
	if (res->status != 200) {
		PLOGE.printf("[HTTP] The server has returned an error: %d", res->status);
		return nullptr;
	}
	nlohmann::json json = nlohmann::json::parse(res->body);
	PLOGI.printf("[HTTP] Response received: %s", json.dump().c_str());
	auto response = session_factory::create_response(json["id"]);
	if (response == nullptr) {
		PLOGF.printf("Invalid request id: %d", (unsigned char)json["id"]);
		return nullptr;
	}
	response->deserialize(json);
	return response;
}
