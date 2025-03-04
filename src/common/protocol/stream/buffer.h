#pragma once

#include <corecrt_malloc.h>

struct buffer {
    void* data;
    size_t size;

    void free() const {
        ::free(this->data);
    }
};
