#include "utils.h"

#include <Windows.h>
#include <cstdio>
#include <psapi.h>
#include <sig.hpp>
#include <plog/Init.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

void utils::init_logger() {
	AllocConsole();

	FILE* newStdout;
	FILE* newStdin;
	freopen_s(&newStdout, "CONOUT$", "w", stdout);
	freopen_s(&newStdin, "CONIN$", "r", stdin);

	SetConsoleTitleA("EAC Emulator");

	static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::debug, &consoleAppender);
}

void* utils::scan_pattern(const char *pattern) {
	static HMODULE handle = GetModuleHandleA(nullptr); // Handle of the game process
	static size_t image_size = 0;
	if (image_size == 0) {
		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), handle, &info, sizeof(MODULEINFO));
		image_size = info.SizeOfImage;
	}

	return Sig::find(handle, image_size, pattern);
}
