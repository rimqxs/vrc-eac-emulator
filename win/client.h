#pragma once

#include "protocol/packet.h"

class client {
    static void receive_loopback();

	static void send_loopback();
public:
    static void connect();

    static void send_packet(const std::shared_ptr<packet>& packet);

	template <typename T>
	static void wait_for_packet() {
		auto packet = std::make_shared<T>();
	}

	static void tick();
};
