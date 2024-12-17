#ifndef AST_H
#define AST_H


#include <stdbool.h>
#include <stddef.h>

#include "ast-node-type.h"

struct AstListNode;
typedef struct AstListNode *AstStack;

#define EMPTY_AST_STACK NULL

struct AstNode {
	enum NodeType nodeType;
	AstStack children;
};

union AstOption {
	char *token;
	struct AstNode node;
};

struct Ast {
	bool isToken;
	union AstOption option;
};

struct Ast createAstToken(const char *token);
struct Ast createAstNode(enum NodeType nodeType, int childCount, ...);

void termAst(struct Ast *);

// TODO: find a better name for the function below
// pushes child to the ast;
// if the ast is terminal transforms
// it into node and pushes the child
void pushChild(struct Ast *ast, struct Ast child);
struct Ast getNthChild(const struct Ast *, size_t n);


struct AstListNode {
	struct Ast ast;
	struct AstListNode *next;
};

void termAstStack(AstStack *);

void pushToAstStack(AstStack *, struct Ast);
void popFromAstStack(AstStack *);

void iterNextAstStack(AstStack **iterPtr);
bool isEndIterAstStack(AstStack *iter);

bool isEmptyAstStack(AstStack);
size_t sizeOfAstStack(AstStack);


#endif