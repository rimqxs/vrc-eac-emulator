#pragma once

#include <string>
#include <utility>

class nullable_string {
	std::string str;
	bool is_null = false;
public:

	nullable_string() {
		is_null = true;
	}

	explicit nullable_string(const char* str) {
		this->str = std::string(str);
	}

	explicit nullable_string(char* str) {
		if (str == nullptr) {
			is_null = true;
			return;
		}

		this->str = std::string(str);
	}

	explicit nullable_string(std::string str) {
		this->str = std::move(str);
	}

	[[nodiscard]] const char* c_str() const {
		if (is_null) {
			return nullptr;
		}

		return str.c_str();
	}

	[[nodiscard]] size_t length() const {
		return str.length();
	}

	bool operator==(void* a) const {
		return a == nullptr && is_null;
	}

	bool operator==(uintptr_t a) const {
		return a == NULL && is_null;
	}
};
