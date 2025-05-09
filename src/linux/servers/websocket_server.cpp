#include "websocket_server.h"

#include <common/constants.h>
#include <common/protocol/packet_codec.h>
#include <hv/WebSocketServer.h>
#include <plog/Log.h>

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "../handlers/handler_registry.h"
#include "hv/WebSocketChannel.h"

std::shared_ptr<hv::WebSocketServer> server;
std::vector<WebSocketChannelPtr> channels;
std::mutex send_mutex, receive_mutex;
std::vector<std::shared_ptr<packet> > send_queued_packets, receive_queued_packets;

void websocket_server::run_server(std::condition_variable& locker, int port) {
	hv::WebSocketService service;
	service.onopen = [&](const WebSocketChannelPtr& channel, const HttpRequestPtr& req) {
		PLOGD.printf("A connection established");
		channels.push_back(channel);
		locker.notify_one();
	};
	service.onmessage = [](const WebSocketChannelPtr& channel, const std::string& msg) {
		receive_mutex.lock();
		read_stream stream(msg.data(), msg.size());
		auto packet = packet_codec::decode(stream);
		if (packet) {
			receive_queued_packets.push_back(packet);
		} else {
			PLOGF.printf("Invalid packet retrieved");
		}
		stream.close();
		receive_mutex.unlock();
	};

	server = std::make_shared<hv::WebSocketServer>(&service);
	server->setHost();
	server->setPort(port);
	server->setThreadNum(4);
	server->run();
}

void websocket_server::launch(int port) {
	PLOGI.printf("Starting server on %d", port);
	std::condition_variable locker;
	std::thread([&]() {
		run_server(locker, port);
	}).detach();

	PLOGI.printf("Waiting for a connection...");
	std::mutex mutex;
	std::unique_lock lock(mutex);
	locker.wait(lock);
}

void websocket_server::send_packet(const std::shared_ptr<packet>& packet) {
	send_mutex.lock();
	send_queued_packets.push_back(packet);
	send_mutex.unlock();
}

void websocket_server::tick() {
	performReceive();
	performSend();
}

void websocket_server::performSend() {
	send_mutex.lock();
	for (auto& packet : send_queued_packets) {
		write_stream stream = packet_codec::encode(packet);
		auto buf = stream.as_buffer();
		for (auto channel : channels) {
			channel->send(static_cast<char*>(buf.data), buf.size, WS_OPCODE_BINARY);
		}
		buf.free();
	}
	send_queued_packets.clear();
	send_mutex.unlock();
}

void websocket_server::performReceive() {
	receive_mutex.lock();
	for (const auto packet : receive_queued_packets) {
		if (const auto handler = handler_registry::get_handler_by_id(packet->get_id())) {
			handler(packet);
		}
	}
	receive_queued_packets.clear();
	receive_mutex.unlock();
}
