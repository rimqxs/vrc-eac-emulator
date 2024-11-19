#include "server.h"

#include <plog/Log.h>

#include "Constants.h"

void server::run() {
    if (socket::init() != NULL) {
        PLOGE.printf("socks::init failed");
        return;
    }

    addrinfo* info;
    if (socket::listen(HOST_PORT, &socket, &info) != NULL) {
        PLOGE.printf("Server setup failed");
        return;
    }

    PLOGI.printf("Server started on localhost:%d! Waiting for connection...", HOST_PORT);
    SOCKET client;
    if (socket::accept(socket, &client) != NULL) {
        PLOGE.printf("Accepting client connection failed");
        return;
    }
    PLOGD.printf("A connection established");
}
