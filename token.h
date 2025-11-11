#ifndef TOKEN_H
#define TOKEN_H

#define TOKENS \
    X(TOKEN_PLUS), \
    X(TOKEN_MINUS), \
    X(TOKEN_DEVIDE),  \
    X(TOKEN_MULTIPLY), \
    X(TOKEN_COLON), \
    X(TOKEN_SEMICOLON), \
    X(TOKEN_QUESTION), \
    X(TOKEN_NOT), \
    X(TOKEN_GT), \
    X(TOKEN_LT), \    
    X(TOKEN_GE), \    
    X(TOKEN_LE), \
    X(TOKEN_NE), \    
    X(TOKEN_EQ), \
    X(TOKEN_ASSIGN), \    
    X(TOKEN_IDENTIFIER), \    
    X(TOKEN_STRING), \
    X(TOKEN_INTEGER), \        
    X(TOKEN_FLOAT), \
    X(TOKEN_LPAREN), \    
    X(TOKEN_RPAREN), \    
    X(TOKEN_LCURLY), \
    X(TOKEN_RCURLY), \      
    X(TOKEN_LSQUARE), \
    X(TOKEN_RSQUARE), \    
    X(TOKEN_COMMA), \    
    X(TOKEN_DOT), \
    X(TOKEN_IF), \              
    X(TOKEN_THEN), \
    X(TOKEN_ELSE), \    
    X(TOKEN_TRUE), \    
    X(TOKEN_FALSE), \
    X(TOKEN_AND), \            
    X(TOKEN_OR), \
    X(TOKEN_DO), \    
    X(TOKEN_WHILE), \    
    X(TOKEN_FOR), \
    X(TOKEN_FUNC), \     
    X(TOKEN_NULL), \
    X(TOKEN_END), \    
    X(TOKEN_PRINT), \    
    X(TOKEN_PRINTLN), \
    X(TOKEN_GIGT), \   
    X(TOKEN_LILT), \
    X(TOKEN_RET), \        
               
                                     
typedef enum {
    #define X(token) token
    TOKENS
    #undef X
} token_type;

const char *tokens[] = {
    #define X(token) #token
    TOKENS
    #undef X
};


typedef struct {
    token_type type;
    char *lexem;
} token_t;



#endif