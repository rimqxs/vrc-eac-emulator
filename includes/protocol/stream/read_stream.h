#pragma once
#include <plog/Log.h>

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

    void close() const {
        if (this->data == nullptr || this->size < 1) {
            PLOGF.printf("invalid data detected at close");
            return;
        }

        free(this->data);
    }
};
