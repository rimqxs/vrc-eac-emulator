#pragma once

#include <ws2tcpip.h>
#define DEFAULT_BUFLEN 10000
#pragma comment(lib, "Ws2_32.lib")

#include <vector>

struct addrinfo;
class socket {
public:
	static int init();

	static int send(SOCKET socket, const void* buf, int len);

	static std::vector<char> recv(SOCKET socket);

	static void close(SOCKET socket);

	// Server
	static int listen(unsigned short port, SOCKET* socketOutput, addrinfo** addrInfoOutput);

	static int accept(SOCKET socket, SOCKET* clientSocketOutput);

	// Client
	static int connect(const char* ipAddress, unsigned short port, SOCKET* socketOutput);
};
