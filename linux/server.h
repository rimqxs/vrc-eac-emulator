#pragma once

#include "socks.h"

class server {
    static inline SOCKET socket;

    static DWORD recvLoop(LPVOID);
public:
    static void run();
};
