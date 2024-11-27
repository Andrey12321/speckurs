#include "buffer.h"
#include <string.h>

int buffer_append(Buffer *buf, const char *data, size_t len) {
    if (buf->size + len > buf->capacity) {
        size_t new_capacity = buf->capacity * 2;
        while (new_capacity < buf->size + len) {
            new_capacity *= 2;
        }
        char *new_data = (char *)realloc(buf->data, new_capacity);
        if (!new_data) {
            return -1; // Memory allocation failed
        }
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    memcpy(buf->data + buf->size, data, len);
    buf->size += len;
    return 0;
}
