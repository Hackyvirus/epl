#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static int pos = 0;
const char* src;

void initLexer(const char* source) {
    src = source;
    pos = 0;
}
typedef struct
{
    const char *word;
    TokenType type;
} Keyword;

static Keyword keywords[] = {
    {"short", TOK_SHORT},
    {"int", TOK_INT},
    {"float", TOK_FLOAT},
    {"double", TOK_DOUBLE},
    {"char", TOK_CHAR},
    {"string", TOK_STRING},
    {"boolean", TOK_BOOLEAN},
    {"null", TOK_NULL},
    {"object", TOK_OBJECT},
    {"bytes", TOK_BYTES},
    {"array", TOK_ARRAY},
    {"pointer", TOK_POINTER},
    {"function", TOK_FUNCTION},
    {"struct", TOK_STRUCT},
    {"union", TOK_UNION},
    {"enum", TOK_ENUM},
    {"typedef", TOK_TYPEDEF},
    {"ppointer", TOK_POINTER_TO_POINTER},
    {"malloc", TOK_DYNAMIC_MEMORY},
    {"bitfield", TOK_BIT_FIELDS},
    {"bigint", TOK_BIG_INT},
    {"tuple", TOK_TUPLE},
    {"list", TOK_LIST},
    {"set", TOK_SET},
    {"dict", TOK_DICT},
    {"class", TOK_CLASS},
    {"complex", TOK_COMPLEX},
    {"generator", TOK_GENERATOR},
    {"async", TOK_ASYNC},
    {"promise", TOK_PROMISE},
    {"variant", TOK_VARIANT},
    {"let", TOK_LET},
    {"const", TOK_CONST},
    {NULL, TOK_EOF} 
};

Token nextToken()
{
    Token t = {TOK_EOF, ""};

    // whitespace handling
    while (isspace(src[pos]))
        pos++;

    if (src[pos] == '\0')
    {
        t.type = TOK_EOF;
        return t;
    }

    // identifiers and Keyword
    if (isalpha(src[pos]))
    {
        int start = pos;
        while (isalnum(src[pos]))
            pos++;
        int length = pos - start;
        strncpy(t.text, src + start, length);
        t.text[length] = '\0';

        for (int i = 0; keywords[i].word != NULL; i++)
        {
            if (strcmp(t.text, keywords[i].word) == 0)
            {
                t.type = keywords[i].type;
                return t;
            }
        }
        t.type = TOK_IDENTIFIER;
    }

    // Number
    if (isdigit(src[pos]))
    {
        int start = pos;
        while (isdigit(src[pos]) || src[pos] == '.')
            pos++;
        int length = pos - start;
        strncpy(t.text, src + start, length);
        t.text[length] = '\0';
        t.type = TOK_NUMBER;
        return t;
    }

    // string literals
    if (src[pos] == '"')
    {
        pos++;
        int start = pos;
        while (src[pos] != '"' && src[pos] != '\0')
            pos++; 
        int length = pos - start;
        strncpy(t.text, src + start, length);
        t.text[length] = '\0';
        if (src[pos] == '"')
            pos++; 
        t.type = TOK_STRING_LITERAL;
        return t;
    }

    // single-char tokens
    char c = src[pos++];
    switch (c) {
       case '+':
        t.type = TOK_PLUS;
        strcpy(t.text, "+");
        break;
    case '-':
        t.type = TOK_MINUS;
        strcpy(t.text, "-");
        break;
    case '*':
        t.type = TOK_MULTIPLY;
        strcpy(t.text, "*");
        break;
    case '/':
        t.type = TOK_DEVIDE;
        strcpy(t.text, "/");
        break;
    case '%':
        t.type = TOK_MODULUS;
        strcpy(t.text, "%");
        break;
    case '=':
        t.type = TOK_ASSIGN;
        strcpy(t.text, "=");
        break;
    case '(':
        t.type = TOK_LEFT_PAREN;
        strcpy(t.text, "(");
        break;
    case ')':
        t.type = TOK_RIGHT_PAREN;
        strcpy(t.text, ")");
        break;
    case '{':
        t.type = TOK_LEFT_CURLYB;
        strcpy(t.text, "{");
        break;
    case '}':
        t.type = TOK_RIGHT_CURLYB;
        strcpy(t.text, "}");
        break;
    case ';':
        t.type = TOK_SEMICOLON;
        strcpy(t.text, ";");
        break;
    case ',':
        t.type = TOK_COMMA;
        strcpy(t.text, ",");
        break;
    case '[':
        t.type = TOK_LEFT_SQRB;
        strcpy(t.text, "[");
        break;
    case ']':
        t.type = TOK_RIGHT_SQRB;
        strcpy(t.text, "]");
        break;
    default:
        t.type = TOK_EOF;
        break;
    }
    return t;
}