#ifndef AST_H
#define AST_H
#include "lexer.h"
typedef struct ASTNode ASTNode; 

typedef enum
{
    NODE_VAR_DECL,
    NODE_NUMBER,
    NODE_BINARY_EXPR,
    NODE_PRINT
} NodeType;

typedef struct
{
    NodeType type;
    union
    {
        struct // variable Declaration
        {
            Token TokenType;
            Token NameToken;
            ASTNode *value;
        } varDecl;

        struct // Number literal
        {
            Token NumberToken;
        } number;

        struct // Binary Expression
        {
            struct ASTNode *left;
            Token OpToken;
            struct ASTNode *right;
        } binaryExpr;
        struct
        { // print statement
            ASTNode *expr;
        } printStmt;
    };

} ASTNode;

#endif