#include "server.h"

#include <thread>
#include <plog/Log.h>

#include "Constants.h"

#include "socket.h"
#include "protocol/packet_codec.h"

SOCKET socket_;
std::vector<std::shared_ptr<packet>> queued_packet;
void server::run() {
    if (socket::init() != NULL) {
        PLOGE.printf("socks::init failed");
        return;
    }

    addrinfo* info;
    if (socket::listen(HOST_PORT, &socket_, &info) != NULL) {
        PLOGE.printf("Server setup failed");
        return;
    }

    PLOGI.printf("Server started on localhost:%d! Waiting for connection...", HOST_PORT);
    SOCKET client;
    if (socket::accept(socket_, &client) != NULL) {
        PLOGE.printf("Accepting client connection failed");
        return;
    }
    PLOGD.printf("A connection established");
}

void server::send_packet(const std::shared_ptr<packet>& packet) {
    queued_packet.push_back(packet);
}
