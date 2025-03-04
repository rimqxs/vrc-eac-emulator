#pragma once
#include <plog/Log.h>

#include "nullable_string.h"

class read_stream {
public:
    void* data;
    size_t size;
    int position;

    read_stream(const void* data, const size_t size) {
        this->data = malloc(size);
        if (this->data == nullptr) {
            PLOGF.printf("malloc failed");
            return;
        }
        memcpy(this->data, data, size);

        this->size = size;
        this->position = 0;
    };

    [[nodiscard]] size_t bytes_remaining() const {
        return this->size - this->position;
    }

    char* read(int rsize) {
        char* ret = static_cast<char*>(data) + position;
        position += rsize;
    	if (bytes_remaining() < 0) { // avoid reading invalid memory
    		PLOGF.printf("read position is oversized");
    		return nullptr;
    	}

        return ret;
    }

    template <typename T>
    T read_as() {
        auto* val = reinterpret_cast<T*>(read(sizeof(T)));
        return *val;
    }

	[[nodiscard]] nullable_string read_string() {
		auto is_valid = read_as<char>();
    	if (!is_valid) {
    		return {};
    	}

		auto length = read_as<unsigned short>();
    	if (length < 0) {
    		return nullable_string("");
    	}
    	void* start = read(length);

    	void* temp = malloc(length + 1 /*NULL byte for end of string*/);
    	memset(temp, 0, length + 1);
    	if (temp == nullptr) {
    		PLOGF.printf("malloc failed");
    		return {};
    	}
    	memcpy(temp, start, length);
    	std::string result = std::string(static_cast<char*>(temp));

    	free(temp);

    	return nullable_string(result);
    }

    void close() const {
        if (this->data == nullptr || this->size < 1) {
            PLOGF.printf("invalid data detected at close");
            return;
        }

        free(this->data);
    }
};
