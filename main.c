#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "dbuf.h"   // dynamic array 
#include "token.h"

typedef struct {
    char *buf;
    size_t len;
} buf_t;

// dynamic array func's 


dbuf_t dbuf_create(dbuf_type type) {
    dbuf_t buf = {
        .len = 0,
        .capacity = DBUF_INIT_SIZE
    };
    switch (type) {
        case STRING:
           buf.buf.c_buf = (char*) malloc(DBUF_INIT_SIZE);
           break;
         case TOKEN:
              buf.buf.t_buf = (token_t*) malloc(sizeof(token_t) * DBUF_INIT_SIZE);
           break;
    }
    return buf;
}

char *push_lexem(lexer_t *l) {
    // TODO : add reallocation
    if (l->lexems.len >= l->lexems.capacity)
    {
        l->lexems.capacity *= 2;
        l->lexems.buf.c_buf = realloc(
           l->lexems.buf.c_buf,
           DBUF_INIT_SIZE * l->lexems.capacity 
        );
    }
    size_t start = l->lexems.len;
    for(size_t i = l->start; i < l->curr; ++i)
        l->lexems.buf.c_buf[l->lexems.len++] = l->src[i];
    l->lexems.buf.c_buf[l->lexems.len++] = '\0';
    return l->lexems.buf.c_buf + start;
}

void push_token(lexer_t *l, token_t t) {
    // TODO : add reallocation
    if (l->lexems.len >= l->lexems.capacity)
    {
        l->lexems.capacity *= 2;
        l->lexems.buf.t_buf = realloc(
           l->lexems.buf.t_buf,
           DBUF_INIT_SIZE * l->lexems.capacity  * sizeof(token_t)
        );
    }    
    l->tokens.buf.t_buf[l->tokens.len++] = t;
}

// lexer func's 

void lexer_init(lexer_t *l, char *buf, size_t len) {
    l->src = buf;
    l->src_len = len;
    l->tokens = dbuf_create(TOKEN);
    l->lexems = dbuf_create(STRING);
    l->start = l->curr = 0;
    l->line = 1;
}

void lexer_free(lexer_t *l) {
    free(l->src);
    free(l->tokens.buf.c_buf);
    free(l->lexems.buf.t_buf);
}


void lexer_tokenize(lexer_t *l) {
    char c;
    while (l->curr < l->src_len) {
        l->start = l->curr;
        c = l->src[l->curr++];
        switch(c) {
            case '+':
              //printf("hitting +\n");
               push_token(
                  l,
                  (token_t) {
                      .type = TOKEN_PLUS,
                      .lexem = push_lexem(l)
                  }
               );
            break;
        }
    }
}

void lexer_print_tokens(lexer_t *l) {
    for (int i = 0; i < l->tokens.len; ++i) {
        printf (
           "%s %s\n",
           tokens[l->tokens.buf.t_buf[i].type],
          l->tokens.buf.t_buf[i].lexem
   
        );
    }
}


void read_file(const char *path, buf_t *b) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        printf("Couldn't open %s !\n", path);
        return;
    }
    fseek(f, 0, SEEK_END);
    const long file_size = ftell(f);
    rewind(f);
    char *buf = (char *)malloc(file_size + 1);
    if (!buf) {
        printf("Couldn't allocate buffer, size %ld\n", file_size);
        goto exit_err;
    }
    size_t bytes_read = fread((void*)buf, 1, file_size, f);
    if (bytes_read != file_size) {
        printf("couldn't read whole file!\n");
        goto exit_err;
    }
    buf[bytes_read] = '\0';
    fclose(f);
    b->buf = buf;
    b->len = file_size;
    return;
    
exit_err:
    fclose (f);   
    free(buf); 
    return;
    
}


int main(int argc, char *argv[])
{
	#if 0 
	if (argc < 2) {
	    printf("Input file not provided !\n");
	    return 1;
	}
	read_file(argv[1]);
	#endif
	buf_t b = {0};
	read_file("./main.ts", &b);
	if (!b.buf) return 1;
	lexer_t l;
	lexer_init(&l, b.buf, b.len); // memory allocated 
	lexer_tokenize(&l);
	lexer_print_tokens(&l);
	lexer_free(&l); // freed 
}