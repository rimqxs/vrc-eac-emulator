#include "server.h"

#include <plog/Log.h>

#define PORT "80"

DWORD server::recvLoop(LPVOID) {
    SOCKET client;
    if (socks::accept(socket, &client) != NULL) {
        PLOGE.printf("Accepting client connection failed");
        return 0;
    }

    return 0;
}

void server::run() {
    if (socks::init() != NULL) {
        PLOGE.printf("socks::init failed");
        return;
    }

    addrinfo* info;
    if (socks::bind(PORT, &socket, &info) != NULL || socks::listen(socket, info) != NULL) {
        PLOGE.printf("Server setup failed");
        return;
    }

    PLOGI.printf("Server started on localhost:%s! Waiting for connection...", PORT);
    CreateThread(nullptr, NULL, recvLoop, nullptr, NULL, nullptr);
}
