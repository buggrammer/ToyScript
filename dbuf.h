#ifndef DBUF_H
#define DBUF_H

#include "token.h"
#define DBUF_INIT_SIZE 2048

typedef enum {
    TOKEN,
    STRING,
} dbuf_type;

typedef struct {
    union {
        char *c_buf;
        token_t *t_buf;
    } buf;
    size_t len;
    size_t capacity;
} dbuf_t;

dbuf_t dbuf_create(dbuf_type type);

#endif