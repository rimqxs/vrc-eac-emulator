#pragma once

#include "socket.h"

class server {
    static inline SOCKET socket;
public:
    static void run();
};
