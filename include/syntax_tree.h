#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "prs.h"

typedef enum yytokentype token_type_t;
typedef YYSTYPE token_value_t;

struct Token {
    token_type_t type;
    token_value_t value;
};

enum SyntaxNodeType {
    SNT_SOURCE,
    SNT_SOURCE_ITEM,

    SNT_TYPE_REF,
    SNT_ARR_SIZE_DEF,

    SNT_FUNC_SIGNATURE,
    SNT_ARG_DEF,
    SNT_LIST_ARG_DEF,

    SNT_STATEMENT_BLOCK,
    SNT_STATEMENT,

    SNT_LIST_INIT_VAR
};

struct SyntaxTree;

struct SyntaxNode {
    enum SyntaxNodeType type;
    size_t childCount;
    struct SyntaxTree *children;
};

// creates an UNINITIALIZED array of SyntaxTree inside a given SyntaxNode
void initSyntaxNode(struct SyntaxNode *, enum SyntaxNodeType, size_t childCount);

union SyntaxOption {
    struct Token token;
    struct SyntaxNode node;
};

struct SyntaxTree {
    bool isLeaf;
    union SyntaxOption option;
};

#define SYNT_OPT(VALUE) (union SyntaxOption)(VALUE)

void initSyntaxTree(struct SyntaxTree *, bool isLeaf, union SyntaxOption option);

struct SyntaxTree *allocSyntaxTree(size_t count);
void freeSyntaxTree(struct SyntaxTree *);

#endif