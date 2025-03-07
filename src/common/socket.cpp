#include "socket.h"

#include <ws2tcpip.h>
#include <plog/Log.h>

static inline WSADATA wsaData;
int socket::init() {
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int socket::send(SOCKET socket, const void* buf, const int len) {
	::send(socket, reinterpret_cast<const char*>(&len), sizeof(int), 0);
	return ::send(socket, static_cast<const char*>(buf), len, 0);
}
std::vector<char> socket::recv(SOCKET socket) {
	char payload_buf[4];
	int bytes_received = ::recv(socket, payload_buf, 4, 0);
	if (bytes_received < 4) {
		PLOGF.printf("Invalid data retrieved");
		return {};
	}

	int data_len = *reinterpret_cast<int*>(payload_buf);
	char* data_buf = static_cast<char*>(malloc(data_len));
	if (data_buf == nullptr) {
		PLOGF.printf("Memory allocation error");
		return {};
	}
	bytes_received = ::recv(socket, data_buf, data_len, 0);
	PLOGD.printf("Received %d bytes (%d bytes required)", data_len, bytes_received);
	if (data_len != bytes_received) {
		MessageBoxA(NULL, "Error", "Invalid data detected!\nPlease contact this error to author of the emulator!", 1);
	}

	std::vector<char> result;
	result.insert(result.begin(), data_buf, data_buf + data_len);
	free(data_buf);

	return result;
}

void socket::close(SOCKET socket) {
    closesocket(socket);
}

int socket::listen(unsigned short port, SOCKET* socketOutput, addrinfo** addrInfoOutput) {
    // Resolve the server address and port
    addrinfo hints{};
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    addrinfo* addrInfo = nullptr;
    int addrResult = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &addrInfo);
    if (addrResult != NULL) {
        PLOGE.printf("getaddrinfo failed with error %d", addrResult);
        return addrResult;
    }

    // Create a SOCKET for the server to listen for client connections
    auto listenSocket = INVALID_SOCKET;
    listenSocket = ::socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        PLOGE.printf("socket failed with error: %ld", WSAGetLastError());
        freeaddrinfo(addrInfo);
        return -1;
    }

    int result = ::bind(listenSocket, addrInfo->ai_addr, (int)addrInfo->ai_addrlen);
    if (result == SOCKET_ERROR) {
        PLOGE.printf("bind failed with error: %d", WSAGetLastError());
        freeaddrinfo(addrInfo);
        closesocket(listenSocket);
        return -1;
    }
    freeaddrinfo(addrInfo);

    result = ::listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        return -1;
    }

    *socketOutput = listenSocket;
    *addrInfoOutput = addrInfo;

    return 0;
}

int socket::accept(SOCKET socket, SOCKET* clientSocketOutput) {
    SOCKET clientSocket = ::accept(socket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        PLOGE.printf("accept failed with error: %d", WSAGetLastError());
        closesocket(socket);
        return -1;
    }

    *clientSocketOutput = clientSocket;

    return 0;
}

int socket::connect(const char* ipAddress, unsigned short port, SOCKET* socketOutput) {
    SOCKET connectSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        PLOGE.printf("socket function failed with error: %ld", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    sockaddr_in clientService{};
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(ipAddress);
    clientService.sin_port = htons(port);

    int result = ::connect(connectSocket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService));
    if (result == SOCKET_ERROR) {
        PLOGE.printf("Connecting to the server failed with error: %ld", WSAGetLastError());
        closesocket(connectSocket);
        return -1;
    }

    *socketOutput = connectSocket;

    return 0;
}
