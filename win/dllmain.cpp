#include <Windows.h>

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "../includes/utils.h"

void init() {
	utils::createConsole();
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, &consoleAppender);

	PLOGD.printf("EOS Emulator initialized correctly");
}

DWORD startServer(LPVOID param) {
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			init();
			CreateThread(nullptr, 0, startServer, nullptr, 0, nullptr);
		break;
	}
	return TRUE;
}
