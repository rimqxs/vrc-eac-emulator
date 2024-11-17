#include "Utils.h"

#include <cstdio>

void Utils::createConsole() {
	AllocConsole();

	FILE* newStdout;
	FILE* newStdin;
	freopen_s(&newStdout, "CONOUT$", "w", stdout);
	freopen_s(&newStdin, "CONIN$", "r", stdin);

	SetConsoleTitleA("EAC Emulator");
}