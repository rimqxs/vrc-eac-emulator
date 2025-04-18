#include "packet_sender.h"

#include <synchapi.h>
#include <winsock.h>

#include <functional>

#include "common/protocol/packet_codec.h"

void packet_sender::run_loopback() {
	while (true) {
		send_mutex.lock();
		for (auto& packet : queued_packet) {
			write_stream stream = packet_codec::encode(packet);
			auto buf = stream.as_buffer();
			if (socket::send(client_socket, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
				PLOGD.printf("Send failed");
			}
			buf.free();
			PLOGD.printf("Packet sent: name=%s id=%d", packet->get_name().c_str(), packet->get_id());
		}
		queued_packet.clear();
		send_mutex.unlock();
		Sleep(30);
	}
}

void packet_sender::start(SOCKET client) {
	client_socket = client;
	std::thread(std::bind(&packet_sender::run_loopback, this)).detach();
}

void packet_sender::send_packet(std::shared_ptr<packet> packet) {
	send_mutex.lock();
	queued_packet.push_back(packet);
	send_mutex.unlock();
}
