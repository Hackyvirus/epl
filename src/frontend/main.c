#include <stdio.h>
#include "ast.h"
#include "lexer.h"
#include "parser.h"

int main() {
    initLexer("int x = 10; print(5);");
    advance();

    ASTNode* decl = parseVariableDeclaration();
    ASTNode* printStmt = parsePrint();

    printf("Parsed variable: %s of type %s with value %s\n",
           decl->varDecl.nameToken.text,
           decl->varDecl.typeToken.text,
           decl->varDecl.value->number.numberToken.text);

    printf("Parsed print statement with value: %s\n",
           printStmt->printStmt.expr->number.numberToken.text);

    return 0;
}
