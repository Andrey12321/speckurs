#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

#define INITIAL_CAPACITY 8

typedef struct {
    size_t capacity;
    size_t size;
    char *data;
} Buffer;

#define buffer_init(buf) do { \
    (buf)->capacity = INITIAL_CAPACITY; \
    (buf)->size = 0; \
    (buf)->data = (char *)malloc((buf)->capacity); \
} while(0)

#define buffer_free(buf) do { \
    free((buf)->data); \
    (buf)->data = NULL; \
    (buf)->capacity = 0; \
    (buf)->size = 0; \
} while(0)

int buffer_append(Buffer *buf, const char *data, size_t len);

#endif // BUFFER_H
