#include <stdio.h>
#include "ast.h"
#include "prs.h"


// TODO: ask about memory deallocating with yyfree


AstStack sourceItems = EMPTY_AST_STACK;


int main(int argc, char **argv) {
    yyparse();
    printf("source item count: %lu\nsource items: %p\n", sizeOfAstStack(sourceItems), sourceItems);

    termAstStack(&sourceItems);

    return 0;
}
