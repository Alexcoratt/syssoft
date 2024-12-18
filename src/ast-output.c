#include <stdlib.h>
#include <string.h>

#include "ast-output.h"

// auxillary functions' declarations

void resizeIndentBuffer(struct IndentCtxt *ctxt, size_t newBufsize);


// definitions

#define MIN_INDENT_BUFFER_SIZE 8
#define INDENT_END_SIZE 2

void initIndentCtxt(struct IndentCtxt *ctxt, size_t bufsize, char fillChar, char endChar) {
	if (bufsize < MIN_INDENT_BUFFER_SIZE)
		bufsize = MIN_INDENT_BUFFER_SIZE;	

	ctxt->bufsize = bufsize;

	char *indentBuffer = malloc(bufsize * sizeof(char));
	memset(indentBuffer, fillChar, bufsize - INDENT_END_SIZE);
	indentBuffer[bufsize - 1] = '\0';
	indentBuffer[bufsize - INDENT_END_SIZE] = endChar;
	ctxt->indentBuffer = indentBuffer;
	
	ctxt->indentLevel = 0;
}

void termIndentCtxt(struct IndentCtxt *ctxt) {
	free(ctxt->indentBuffer);
}

void increaseIndentLevel(struct IndentCtxt *ctxt) {
	++ctxt->indentLevel;
	
	const size_t bufsize = ctxt->bufsize;
	
	size_t rightShift = ctxt->indentLevel + INDENT_END_SIZE;
	if (rightShift >= bufsize)
		resizeIndentBuffer(ctxt, bufsize * 2);
}

void resizeIndentBuffer(struct IndentCtxt *ctxt, size_t newBufsize) {
	size_t oldBufsize = ctxt->bufsize;

	if (newBufsize <= oldBufsize)
		return;

	char endChar = ctxt->indentBuffer[oldBufsize - INDENT_END_SIZE];
	char fillChar = *ctxt->indentBuffer;
	
	ctxt->indentBuffer = realloc(ctxt->indentBuffer, newBufsize);
	char *oldEndCharPtr = ctxt->indentBuffer + oldBufsize - INDENT_END_SIZE;

	memset(oldEndCharPtr, fillChar, newBufsize - oldBufsize);
	ctxt->indentBuffer[newBufsize - 1] = '\0';
	ctxt->indentBuffer[newBufsize - INDENT_END_SIZE] = endChar;

	ctxt->bufsize = newBufsize;
}

void decreaseIndentLevel(struct IndentCtxt *ctxt) {
	--ctxt->indentLevel;
}

const char *getIndentString(const struct IndentCtxt *ctxt) {
	size_t rightShift = ctxt->indentLevel + INDENT_END_SIZE;
	return ctxt->indentBuffer + ctxt->bufsize - rightShift;
}

void fprintAst(FILE *ofptr, const struct Ast *astPtr, struct IndentCtxt *indentCtxt) {
	const char *indent = getIndentString(indentCtxt);

	if (astPtr->isToken) {
		const char *token = astPtr->option.token;
		fprintf(ofptr, "%s \'%s\'\n", indent, token);
	} else {
		enum AstNodeType nodeType = astPtr->option.node.nodeType;
		const char *nodeTypeStr = getAstNodeTypeString(nodeType);
		fprintf(ofptr, "%s %s\n", indent, nodeTypeStr);

		increaseIndentLevel(indentCtxt);

		const struct AstNode *astNodePtr = &astPtr->option.node;
		for (
			AstStack child = astNodePtr->children; 
			child != EMPTY_AST_STACK;
			child = child->next
		)
			fprintAst(ofptr, &child->ast, indentCtxt);

		decreaseIndentLevel(indentCtxt);
	}
}

#define CASE(ITEM) case ITEM: return #ITEM;

const char *getAstNodeTypeString(enum AstNodeType item) {
	switch(item) {
		CASE(NT_ADD_EXPR)
		CASE(NT_SUB_EXPR)
		CASE(NT_MUL_EXPR)
		CASE(NT_DIV_EXPR)

		CASE(NT_CALL_EXPR)
		CASE(NT_INDEX_EXPR)
		CASE(NT_ASSIGN_EXPR)

		CASE(NT_EXPR_LIST)
		CASE(NT_INIT_VAR_LIST)
		CASE(NT_ARG_DEF_LIST)
		CASE(NT_ARR_SIZE_DEF_LIST)
		CASE(NT_SRC)

		CASE(NT_INIT_VAR_STMT)
		CASE(NT_IF_STMT)
		CASE(NT_IF_ELSE_STMT)
		CASE(NT_WHILE_STMT)
		CASE(NT_DO_WHILE_STMT)
		CASE(NT_BREAK_STMT)
		CASE(NT_STMT_BLOCK)
		CASE(NT_STMT_BLOCK_INNER)

		CASE(NT_FUNC_SIGNATURE)
		CASE(NT_FUNC)
		CASE(NT_TYPE_REF)
		CASE(NT_ARG_DEF)

		default: return "UNKNOWN_NODE_TYPE";
	}
}

#undef CASE