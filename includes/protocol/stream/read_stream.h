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

    char* read(int rsize) {
        int new_position = rsize + this->position;
        if (new_position >= this->size) { // avoid reading invalid memory
            PLOGF.printf("read position is oversized");
            return nullptr;
        }

        char* ret = static_cast<char*>(data) + position;
        position += new_position;
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
