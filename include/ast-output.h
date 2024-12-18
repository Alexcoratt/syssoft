#ifndef AST_OUTPUT_H
#define AST_OUTPUT_H

#include <stdio.h>
#include "ast.h"

struct IndentCtxt {
	size_t bufsize;
	char *indentBuffer;
	size_t indentLevel;
};

void initIndentCtxt(struct IndentCtxt *ctxt, size_t bufsize, char fillChar, char endChar);
void termIndentCtxt(struct IndentCtxt *ctxt);

void increaseIndentLevel(struct IndentCtxt *ctxt);
void decreaseIndentLevel(struct IndentCtxt *ctxt);
const char *getIndentString(const struct IndentCtxt *ctxt);


const char *getAstNodeTypeString(enum AstNodeType);


void fprintAst(FILE *ofptr, const struct Ast *astPtr, struct IndentCtxt *indentCtxt);


// TODO: implement
void fprintAstAsGraphviz(FILE *ofptr, const struct Ast *astPtr);


#endif