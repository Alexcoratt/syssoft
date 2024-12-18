#include "ast-node-type.h"

const char *getAstNodeTypeString(enum AstNodeType item) {
	switch(item) {
		case NT_ADD_EXPR: return "NT_ADD_EXPR";
		case NT_SUB_EXPR: return "NT_SUB_EXPR";
		case NT_MUL_EXPR: return "NT_MUL_EXPR";
		case NT_CALL_EXPR: return "NT_CALL_EXPR";
		case NT_INDEX_EXPR: return "NT_INDEX_EXPR";
		case NT_EXPR_LIST: return "NT_EXPR_LIST";
		case NT_INIT_VAR_LIST: return "NT_INIT_VAR_LIST";
		case NT_ARG_DEF_LIST: return "NT_ARG_DEF_LIST";
		case NT_ARR_SIZE_DEF_LIST: return "NT_ARR_SIZE_DEF_LIST";
		case NT_SRC: return "NT_SRC";
		case NT_INIT_VAR_STMT: return "NT_INIT_VAR_STMT";
		case NT_IF_STMT: return "NT_IF_STMT";
		case NT_IF_ELSE_STMT: return "NT_IF_ELSE_STMT";
		case NT_WHILE_STMT: return "NT_WHILE_STMT";
		case NT_DO_WHILE_STMT: return "NT_DO_WHILE_STMT";
		case NT_BREAK_STMT: return "NT_BREAK_STMT";
		case NT_STMT_BLOCK: return "NT_STMT_BLOCK";
		case NT_STMT_BLOCK_INNER: return "NT_STMT_BLOCK_INNER";
		case NT_FUNC_SIGNATURE: return "NT_FUNC_SIGNATURE";
		case NT_FUNC: return "NT_FUNC";
		case NT_TYPE_REF: return "NT_TYPE_REF";
		case NT_ARG_DEF: return "NT_ARG_DEF";
		default: return "UNKNOWN_ENUM_ITEM";
	}
}