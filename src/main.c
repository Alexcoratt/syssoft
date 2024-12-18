#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ast.h"
#include "prs.h"


// TODO: ask about memory deallocating with yyfree

// auxillary method declarations

void fprintAst(FILE *ofptr, const struct Ast *, size_t indentSize);
void fprintAstToken(FILE *ofptr, const char *token, size_t indentSize);
void fprintAstNode(FILE *ofptr, const struct AstNode *, size_t indentSize);

char *createIndentLine(size_t indentSize);


// definitions

AstStack sourceItems = EMPTY_AST_STACK;


int main(int argc, char **argv) {
    yyparse();

    // TODO: replace AstStack of sourceItems with struct Ast
    size_t srcItemCount = sizeOfAstStack(sourceItems);
    printf("source item count: %lu\n", srcItemCount);

    fprintAst(stdout, &sourceItems->ast, 0);

    termAstStack(&sourceItems);

    return 0;
}

void fprintAst(FILE *ofptr, const struct Ast *astPtr, size_t indentSize) {
	if (astPtr->isToken) {
		const char *token = astPtr->option.token;
		fprintAstToken(ofptr, token, indentSize);
	} else {
		const struct AstNode *astNodePtr = &astPtr->option.node;
		fprintAstNode(ofptr, astNodePtr, indentSize);
	}
}

char *createIndentLine(size_t indentSize) {
	char *indentLine = malloc((indentSize + 3) * sizeof(char));
	memset(indentLine, '|', indentSize);
	strcpy(indentLine + indentSize, "--");
	return indentLine;
}

void fprintAstToken(FILE *ofptr, const char *token, size_t indentSize) {
	char *indentLine = createIndentLine(indentSize);
	fprintf(ofptr, "%s \'%s\'\n", indentLine, token);
	free(indentLine);
}

void fprintAstNode(FILE *ofptr, const struct AstNode *astNodePtr, size_t indentSize) {
	char *indentLine = createIndentLine(indentSize);

	const char *nodeTypeString = getAstNodeTypeString(astNodePtr->nodeType);
	fprintf(ofptr, "%s %s\n", indentLine, nodeTypeString);

	size_t newIndentSize = indentSize + 1;

	for (
		AstStack child = astNodePtr->children;
		child != EMPTY_AST_STACK;
		child = child->next
	)
		fprintAst(ofptr, &child->ast, newIndentSize);

	free(indentLine);
}
