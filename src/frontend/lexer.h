#ifndef LEXER_H
#define LEXER_H

void initLexer(const char* source);

typedef enum {
    TOK_EOF,

    // identifiers & literals
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_STRING_LITERAL,
    TOK_CHAR_LITERAL,

    // DATA TYPES
    TOK_SHORT,
    TOK_INT,
    TOK_FLOAT,
    TOK_DOUBLE,
    TOK_CHAR,
    TOK_STRING,
    TOK_BOOLEAN,
    TOK_NULL,
    TOK_OBJECT,
    TOK_BYTES,
    TOK_ARRAY,
    TOK_POINTER,
    TOK_FUNCTION,
    TOK_STRUCT,
    TOK_UNION,
    TOK_ENUM,
    TOK_TYPEDEF,
    TOK_POINTER_TO_POINTER,
    TOK_DYNAMIC_MEMORY,
    TOK_BIT_FIELDS,
    TOK_BIG_INT,
    TOK_TUPLE,
    TOK_LIST,
    TOK_SET,
    TOK_DICT,
    TOK_CLASS,
    TOK_COMPLEX,
    TOK_GENERATOR,
    TOK_ASYNC,
    TOK_PROMISE,
    TOK_VARIANT,

    // VAR DECL
    TOK_LET,
    TOK_CONST,

    // OPERATORS
    TOK_PLUS,
    TOK_MINUS,
    TOK_DEVIDE,
    TOK_MULTIPLY,
    TOK_MODULUS,
    TOK_ASSIGN,  // <= don’t forget this one!

    // DELIMITERS
    TOK_LEFT_PAREN,
    TOK_RIGHT_PAREN,
    TOK_LEFT_CURLYB,
    TOK_RIGHT_CURLYB,
    TOK_SEMICOLON,
    TOK_COMMA,
    TOK_LEFT_SQRB,
    TOK_RIGHT_SQRB
} TokenType;


typedef struct {
    TokenType type;
    char text[256]; 
} Token;

extern const char *src;   

Token nextToken(void);

#endif