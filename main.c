#include <stdio.h>

#include "ast.h"
#include "prs.h"
#include "ast-output.h"


// TODO: ask about memory deallocating with yyfree


AstStack sourceItems = EMPTY_AST_STACK;


int main(int argc, char **argv) {
	yyparse();

	// TODO: replace AstStack of sourceItems with struct Ast
	size_t srcItemCount = sizeOfAstStack(sourceItems);
	printf("source item count: %lu\n", srcItemCount);

	struct IndentCtxt ctxt;
	initIndentCtxt(&ctxt, 128, '|', '>');
	fprintAst(stdout, &sourceItems->ast, &ctxt);

	termIndentCtxt(&ctxt);
	termAstStack(&sourceItems);
	return 0;
}
