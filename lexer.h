
#ifndef LEXER_H 
#define LEXER_H

#include <stdint.h>
#include "dbuf.h"

typedef struct {
    const char *src;
    size_t src_len;
    dbuf_t tokens;
    dbuf_t lexems;
    uint32_t start;
    uint32_t curr;
    uint32_t line; 
    
} lexer_t;

void lexer_init(lexer_t *l, char *buf, size_t len);
void lexer_tokenize(lexer_t *l);

#endif