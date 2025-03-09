#pragma once

class http_server {
	static inline int port;

	static void init();
public:
	static void run(int port);
};
