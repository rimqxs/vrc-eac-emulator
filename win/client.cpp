#include "client.h"

#include <plog/Log.h>

#include "Constants.h"
#include "socket.h"
#include "protocol/packet_codec.h"

SOCKET socket_;
std::vector<std::shared_ptr<packet>> queued_packet;
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
}

void client::send_packet(const std::shared_ptr<packet>& packet) {
    queued_packet.push_back(packet);
}
