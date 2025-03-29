#pragma once

#include <plog/Severity.h>

#include <optional>
#include <string>

class utils {
public:
	static void create_console();

	static void init_logger(bool use_colored, plog::Severity severity);

	static void sleep(unsigned int ms);

	static std::optional<std::string> read_file(const std::string& path);

	static void write_file(const std::string& path, const std::string& content);
};
