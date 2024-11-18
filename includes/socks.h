#pragma once

#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

class socks {
    static inline WSADATA wsaData;

    static int resolveAddrInfo(const char* port, addrinfo** addrInfoOutput);
public:
    static int init();

    static int bind(const char* port, SOCKET* socketOutput, addrinfo** addrInfoOutput);

    static int listen(SOCKET socket, addrinfo* addrInfo);

    static int accept(SOCKET socket, SOCKET* clientSocketOutput);

    static void close(SOCKET socket);
};
