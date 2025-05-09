#include "emulator_client.h"

#include <memory>

#include "common/api/session_factory.h"
#include "handler/handlers/client_packet_handler.h"
#include "handler/packet_handler.h"
#include "hv/requests.h"
#include "sock/packet_sender.h"

emulator_client::emulator_client(std::string address, int http_port) : address(address), http_port(http_port), client() {
	instance = this;
}

void emulator_client::connect(int tcp_port) {
	client.run(address, tcp_port);
	sender = std::make_shared<packet_sender>(client.getWebsocketClient());
	sender->start();
	std::shared_ptr<packet_handler> handler = std::make_shared<client_packet_handler>(sender);
	client.set_packet_handler(handler);
}

void emulator_client::send_packet(std::shared_ptr<packet> packet) {
	sender->send_packet(packet);
}

emulator_client* emulator_client::get_instance() {
	return instance;
}

std::shared_ptr<response> emulator_client::_request(std::shared_ptr<request> const& request) {
	nlohmann::json serialized;
	request->serialize(serialized);

	auto res = requests::post(std::format("http://{}:{}/task", address, http_port).c_str(), serialized.dump());
	if (res->status_code != 200) {
		PLOGE.printf("[HTTP] The server has returned an error: %d", res->status_code);
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
