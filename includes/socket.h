#pragma once

#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

class socket {
    static inline WSADATA wsaData;
public:
    static int init();

    static void send(SOCKET socket, const void* buf, int len);

    static void close(SOCKET socket);

    // Server
    static int listen(unsigned short port, SOCKET* socketOutput, addrinfo** addrInfoOutput);

    static int accept(SOCKET socket, SOCKET* clientSocketOutput);

    // Client
    static int connect(const char* ipAddress, unsigned short port, SOCKET* socketOutput);
};
