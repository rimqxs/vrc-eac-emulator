#pragma once
#include "buffer.h"

#include <vector>
#include <plog/Log.h>

#include "nullable_string.h"

class write_stream {
public:
    std::vector<char> buffer;

    void write(const void* data, size_t size) {
        for (size_t i = 0; i < size; i++) {
            const char* at = static_cast<const char*>(data) + i;
            buffer.push_back(*at);
        }
    }

    template <typename T>
    void write_as(T val) {
        write(&val, sizeof(val));
    }

	void write_string(const nullable_string& string) {
    	if (string == nullptr) {
    		write_as<char>(0); // is valid
    		write_as<unsigned short>(0);
    		return;
    	}

    	write_as<char>(1); // is valid
    	short len = strlen(string.c_str());
    	write_as<unsigned short>(len);
    	if (len == 0) {
    		write_as<unsigned short>(0);
    		return;
    	}

    	if (len > USHRT_MAX) {
		    PLOGF.printf("Max len allowed for string oversized");
	    	return;
	    }

    	write(string.c_str(), string.length());
    }

    ::buffer as_buffer() const {
        if (buffer.empty()) {
            return {
                nullptr,
                0
            };
        }

        void* copiedBuffer = malloc(buffer.size());
        if (copiedBuffer == nullptr) {
            PLOGF.printf("malloc failed");
        }

        memcpy(copiedBuffer, buffer.data(), buffer.size());

        return {
            copiedBuffer,
            buffer.size()
        };
    }
};
