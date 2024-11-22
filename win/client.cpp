#include "client.h"

#include <future>
#include <plog/Log.h>

#include "socket.h"
#include "constants.h"
#include "client_packet_handler.h"
#include "protocol/packet_codec.h"
#include "protocol/packets/handshake_packet.h"

SOCKET socket_;
std::mutex mutex;
std::vector<std::shared_ptr<packet>> queued_packet;

#define DEFAULT_BUFLEN 512

void client::receive_handler() {
    PLOGD.printf("Recv loop started");

    bool running = true;
    char buf[DEFAULT_BUFLEN];
    int buf_len = DEFAULT_BUFLEN;
    while (running) {
        int received_len = recv(socket_, buf, buf_len, 0);
        if (received_len <= 0) {
            PLOGW.printf("Connection closed");
            running = false;
            continue;
        }

        read_stream stream(buf, received_len);
        while (stream.bytes_remaining() > 0) {
            auto packet = packet_codec::decode(stream);
            if (packet == nullptr) {
                PLOGF.printf("packet decoding failed");
                return;
            }

            client_packet_handler::handle(packet);
        }
		stream.close();
    }
}

void client::send_handler() {
    PLOGD.printf("Send loop started");
    bool running = true;
    while (running) {
        mutex.lock();
        for (auto& packet : queued_packet) {
            write_stream stream = packet_codec::encode(packet);

            auto buf = stream.as_buffer();
            if (socket::send(socket_, buf.data, static_cast<int>(buf.size)) == SOCKET_ERROR) {
                PLOGD.printf("Send failed");
                running = false;
            }
            buf.free();

            PLOGD.printf("Packet sent: name=%s id=%d", packet->get_name().c_str(), packet->get_id());
        }
        queued_packet.clear();
        mutex.unlock();
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

    std::thread(send_handler).detach();
    std::thread(receive_handler).detach();

    // Send handshake packet
    auto packet = std::make_shared<handshake_packet>();
    packet->timestamp = std::time(nullptr);
    send_packet(packet);
}

void client::send_packet(const std::shared_ptr<packet>& packet) {
    mutex.lock();
    queued_packet.push_back(packet);
    mutex.unlock();
}
