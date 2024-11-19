#include "client.h"

#include <future>
#include <thread>
#include <plog/Log.h>

#include "socket.h"
#include "constants.h"
#include "protocol/packet_codec.h"

SOCKET socket_;
std::mutex mutex;
std::vector<std::shared_ptr<packet>> queued_packet;

void client::receive_handler() {
    PLOGD.printf("Recv loop started");
    bool running = true;
    while (running) {

    }
}

void client::send_handler() {
    PLOGD.printf("Send loop started");
    bool running = true;
    while (running) {
        mutex.lock();
        for (auto& packet : queued_packet) {
            write_stream stream;
            packet->encode(stream);

            auto buf = stream.as_buffer();
            if (socket::send(socket_, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
                PLOGD.printf("Send failed");
                running = false;
            }
            buf.free();
        }
        queued_packet.clear();
        mutex.unlock();

        Sleep(10);
    }
}

void client::connect() {
    if (socket::init() != NULL) {
        PLOGE.printf("socks::init failed");
        return;
    }

    PLOGD.printf("Connecting to the server %s:%d!", HOST_IP_ADDR, HOST_PORT);
    while (socket::connect(HOST_IP_ADDR, HOST_PORT, &socket_)) {
        PLOGW.printf("socks::connect failed, retrying after 5 seconds...");
        Sleep(5000);
    }
    PLOGI.printf("Connected to the server!");

    auto receive = std::async(std::launch::async, receive_handler);
    auto send = std::async(std::launch::async, send_handler);
    receive.wait();
    send.wait();
}

void client::send_packet(const std::shared_ptr<packet>& packet) {
    mutex.lock();
    queued_packet.push_back(packet);
    mutex.unlock();
}
