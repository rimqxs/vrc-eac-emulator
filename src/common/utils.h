#pragma once

#include <string>
#include <optional>

class utils {
public:
	static void init_logger(bool use_colored);

	static void sleep(unsigned int ms);

	static std::optional<std::string> read_file(const std::string& path);

	static void write_file(const std::string& path, const std::string& content);
};
