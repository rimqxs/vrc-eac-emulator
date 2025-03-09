#include "utils.h"

#include <Windows.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <thread>

void utils::init_logger(bool use_colored) {
	AllocConsole();

	FILE* newStdout;
	FILE* newStdin;
	freopen_s(&newStdout, "CONOUT$", "w", stdout);
	freopen_s(&newStdin, "CONIN$", "r", stdin);

	SetConsoleTitleA("EAC Emulator");

	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
	static plog::ColorConsoleAppender<plog::TxtFormatter> coloredConsoleAppender;
	plog::IAppender* appender = use_colored ? &coloredConsoleAppender : &consoleAppender;
	plog::init(plog::verbose, appender);
}

void utils::sleep(unsigned int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
std::optional<std::string> utils::read_file(const std::string& path) {
	std::ifstream stream = std::ifstream(path);
	if (!stream) {
		stream.close();
		return std::nullopt;
	}

	std::string content = std::string(std::istreambuf_iterator(stream), std::istreambuf_iterator<char>());
	stream.close();
	return std::optional{content};
}
void utils::write_file(const std::string& path, const std::string& content) {
	std::ofstream stream = std::ofstream(path);
	stream << content;
	stream.close();
}
