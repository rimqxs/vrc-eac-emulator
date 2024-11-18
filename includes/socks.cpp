#include "socks.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <plog/Log.h>

int socks::resolveAddrInfo(const char* port, addrinfo** addrInfoOutput) {
    // Resolve the server address and port
    addrinfo hints{};
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    addrinfo* addrInfo;
    int addrResult = getaddrinfo(nullptr, port, &hints, &addrInfo);
    if (addrResult != NULL) {
        PLOGE.printf("getaddrinfo failed with error %d", addrResult);
        return addrResult;
    }

    *addrInfoOutput = addrInfo;

    return 0;
}

int socks::init() {
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int socks::bind(const char* port, SOCKET* socketOutput, addrinfo** addrInfoOutput) {
    addrinfo* addrInfo = nullptr;
    if (resolveAddrInfo(port, &addrInfo) != NULL) {
        PLOGF.printf("resolveAddrInfo failed");
        return -1;
    }

    // Create a SOCKET for the server to listen for client connections
    auto listenSocket = INVALID_SOCKET;
    listenSocket = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        PLOGE.printf("socket failed with error: %ld", WSAGetLastError());
        freeaddrinfo(addrInfo);
        WSACleanup();
        return -1;
    }

    *socketOutput = listenSocket;
    *addrInfoOutput = addrInfo;

    return 0;
}

int socks::listen(SOCKET socket, addrinfo* addrInfo) {
    int result = ::bind(socket, addrInfo->ai_addr, (int)addrInfo->ai_addrlen);
    if (result == SOCKET_ERROR) {
        PLOGE.printf("bind failed with error: %d", WSAGetLastError());
        freeaddrinfo(addrInfo);
        closesocket(socket);
        WSACleanup();
        return -1;
    }
    freeaddrinfo(addrInfo);

    result = ::listen(socket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(socket);
        WSACleanup();
        return -1;
    }

    return 0;
}

int socks::accept(SOCKET socket, SOCKET* clientSocketOutput) {
    SOCKET clientSocket = ::accept(socket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        PLOGE.printf("accept failed with error: %d", WSAGetLastError());
        closesocket(socket);
        WSACleanup();
        return -1;
    }

    *clientSocketOutput = clientSocket;

    return 0;
}

void socks::close(SOCKET socket) {
    closesocket(socket);
}
