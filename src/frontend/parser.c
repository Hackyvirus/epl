#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "lexer.h"

Token currentToken;

void advance()
{
    currentToken = nextToken();
}

ASTNode *parseNumber()
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->number.NumberToken = currentToken;
    advance();
    return node;
}

int isTypeToken(TokenType t)
{
    switch (t)
    {
    case TOK_SHORT:
    case TOK_INT:
    case TOK_FLOAT:
    case TOK_DOUBLE:
    case TOK_CHAR:
    case TOK_STRING:
    case TOK_BOOLEAN:
    case TOK_NULL:
    case TOK_OBJECT:
    case TOK_BYTES:
    case TOK_ARRAY:
    case TOK_POINTER:
    case TOK_FUNCTION:
    case TOK_STRUCT:
    case TOK_UNION:
    case TOK_ENUM:
    case TOK_TYPEDEF:
    case TOK_POINTER_TO_POINTER:
    case TOK_DYNAMIC_MEMORY:
    case TOK_BIT_FIELDS:
    case TOK_BIG_INT:
    case TOK_TUPLE:
    case TOK_LIST:
    case TOK_SET:
    case TOK_DICT:
    case TOK_CLASS:
    case TOK_COMPLEX:
    case TOK_GENERATOR:
    case TOK_ASYNC:
    case TOK_PROMISE:
    case TOK_VARIANT:
        return 1;
    default:
        return 0;
    }
}

ASTNode *parseExpression()
{
    ASTNode *left = parseNumber();

    while (currentToken.type == TOK_PLUS || currentToken.type == TOK_MINUS)
    {
        Token op = currentToken;
        advance();

        ASTNode *right = parseNumber();

        ASTNode *binExpr = malloc(sizeof(ASTNode));
        binExpr->type = NODE_BINARY_EXPR;
        binExpr->binaryExpr.left = left;
        binExpr->binaryExpr.OpToken = op;
        binExpr->binaryExpr.right = right;
        left = binExpr;
    }

    return left;
}

ASTNode *parseVariableDeclaration()
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL;

    if (!isTypeToken(currentToken.type))
    {
        printf("Error: expected type\n");
        exit(1);
    }
    node->varDecl.TokenType = currentToken;
    advance();

    if (currentToken.type != TOK_IDENTIFIER)
    {
        printf("Error: expected variable name\n");
        exit(1);
    }
    node->varDecl.NameToken = currentToken;
    advance();

    if (currentToken.type != TOK_ASSIGN)
    {
        printf("Error: expected '='\n");
        exit(1);
    }
    advance();

    node->varDecl.value = parseExpression();

    if (currentToken.type != TOK_SEMICOLON)
    {
        printf("Error: expected ';'\n");
        exit(1);
    }
    advance();
    return node;
}
