#pragma once

#include "common/api/request.h"
#include "common/api/response.h"
#include "common/protocol/packet.h"

class client {
	static void receive_loopback();

	static void send_loopback();

	static std::shared_ptr<response> _request(std::shared_ptr<request> const& request);

   public:
	static void connect();

	static void send_packet(const std::shared_ptr<packet>& packet);

	template <typename RES>
	static std::shared_ptr<RES> request(std::shared_ptr<request> const& request) {
		return std::static_pointer_cast<RES>(_request(request));
	}

	static void tick();
};
