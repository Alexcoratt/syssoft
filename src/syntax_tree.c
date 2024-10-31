#include <stdlib.h>
#include "syntax_tree.h"

void initSyntaxNode(struct SyntaxNode *node, enum SyntaxNodeType type, size_t childCount) {
    node->type = type;
    node->childCount = childCount;
    node->children = allocSyntaxTree(childCount);
}

struct SyntaxTree *allocSyntaxTree(size_t count) {
    return malloc(count * sizeof(struct SyntaxTree));
}

void initSyntaxTree(struct SyntaxTree *tree, bool isLeaf, union SyntaxOption option) {
    tree->isLeaf = isLeaf;
    tree->option = option;
}

void freeSyntaxTree(struct SyntaxTree *tree) {
    free(tree);
}