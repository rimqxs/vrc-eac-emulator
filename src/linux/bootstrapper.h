#pragma once

class bootstrapper {
	static inline int tcp_port;
	static inline int http_port;

	static int __stdcall Dummy_WinMain();

	static void hook_winmain();

   public:
	static void main(int tcp_port, int http_port);
};
