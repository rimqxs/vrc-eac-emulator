#pragma once
#include "buffer.h"

class write_stream {
public:
    std::vector<char> buffer;

    void write(void* data, size_t size) {
        for (size_t i = 0; i < size; i++) {
            const char* at = static_cast<char*>(data) + i;
            buffer.push_back(*at);
        }
    }

    template <typename T>
    void write_as(T val) {
        write(&val, sizeof(val));
    }

    ::buffer as_buffer() {
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
