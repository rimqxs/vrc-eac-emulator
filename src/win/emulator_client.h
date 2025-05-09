#pragma once

#include <memory>

#include "common/api/request.h"
#include "common/api/response.h"
#include "common/protocol/packet.h"
#include "sock/packet_sender.h"
#include "sock/websocket_client.h"

class emulator_client {
	static inline emulator_client* instance;

	std::string address;
	int http_port;

	websocket_client client;
	std::shared_ptr<packet_sender> sender;

public:
	emulator_client(std::string address, int http_port);

	void connect(int tcp_port);

	void send_packet(std::shared_ptr<packet> packet);

	template <typename RES>
	std::shared_ptr<RES> send_request(std::shared_ptr<request> const& request) {
		return std::static_pointer_cast<RES>(_request(request));
	}

	static emulator_client* get_instance();

private:
	std::shared_ptr<response> _request(std::shared_ptr<request> const& request);
};
