#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"


// auxillary functions' declarations

char *createStrCopy(const char *str);

AstStack createAstStack(int count, struct Ast *);


// definitions

struct Ast createAstToken(const char *token) {
    char *tokenCopy = createStrCopy(token);
    return (struct Ast){ true, { .token = tokenCopy } };
}

char *createStrCopy(const char *str) {
    size_t size = strlen(str) + 1;
    char *strCopy = (char *)malloc(size * sizeof(char));
    strncpy(strCopy, str, size);
    return strCopy;
}


struct Ast createAstNode(enum NodeType nodeType, int childCount, ...) {
    va_list args;
    va_start(args, childCount);

    struct Ast asts[childCount];
    for (int i = 0; i < childCount; ++i)
        asts[i] = va_arg(args, struct Ast);

    va_end(args);

    AstStack children = createAstStack(childCount, asts);
    struct AstNode node = { nodeType, children };
    struct Ast res = { false, { .node = node } };
    
    return res;
}

AstStack createAstStack(int count, struct Ast *asts) {
    AstStack first = EMPTY_AST_STACK;
    AstStack *astStackIter = &first;

    for (int i = 0; i < count; ++i) {
        pushToAstStack(astStackIter, asts[i]);
        iterNextAstStack(&astStackIter);
    }

    return first;
}

void pushToAstStack(AstStack *astStackPtr, struct Ast ast) {
    AstStack newFirst = malloc(sizeof(struct AstListNode));
    newFirst->ast = ast;
    newFirst->next = *astStackPtr;
    *astStackPtr = newFirst;
}

void iterNextAstStack(AstStack **iterPtr) {
    if (!isEndIterAstStack(*iterPtr))
        *iterPtr = &(**iterPtr)->next;
}

bool isEndIterAstStack(AstStack *iter) {
    return (*iter) == EMPTY_AST_STACK;
}

void termAst(struct Ast *ast) {
    if (ast->isToken)
        free(ast->option.token);
    else
        termAstStack(&ast->option.node.children);
}

void termAstStack(AstStack *astStackPtr) {
    while (!isEmptyAstStack(*astStackPtr))
        popFromAstStack(astStackPtr);
}

void popFromAstStack(AstStack *astStackPtr) {
    AstStack nodeToRemove = *astStackPtr;
    termAst(&nodeToRemove->ast);
    *astStackPtr = (*astStackPtr)->next;
    free(nodeToRemove);
}

bool isEmptyAstStack(AstStack astStack) {
    return astStack == EMPTY_AST_STACK;
}

size_t sizeOfAstStack(AstStack astStack) {
    size_t res = 0;
    for (AstStack *iter = &astStack; !isEndIterAstStack(iter); iterNextAstStack(&iter)) {
        ++res;
    }
    return res;
}
