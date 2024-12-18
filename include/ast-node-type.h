#ifndef AST_NODE_TYPE_H
#define AST_NODE_TYPE_H

enum AstNodeType {
	// # expressions

	// ## arithmetic expressions

	NT_ADD_EXPR,
	NT_SUB_EXPR,
	NT_MUL_EXPR,
	NT_DIV_EXPR,

	// ## special expressions

	NT_CALL_EXPR,
	NT_INDEX_EXPR,


	// # lists
	
	NT_EXPR_LIST,
	NT_INIT_VAR_LIST,
	NT_ARG_DEF_LIST,
	NT_ARR_SIZE_DEF_LIST,
	NT_SRC,


	// # statements

	NT_INIT_VAR_STMT,
	NT_IF_STMT,
	NT_IF_ELSE_STMT,
	NT_WHILE_STMT,
	NT_DO_WHILE_STMT,
	NT_BREAK_STMT,

	NT_STMT_BLOCK,
	NT_STMT_BLOCK_INNER,


	// # functions
	NT_FUNC_SIGNATURE,
	NT_FUNC,


	// # other
	
	NT_TYPE_REF,
	NT_ARG_DEF,
};

const char *getAstNodeTypeString(enum AstNodeType);

#endif