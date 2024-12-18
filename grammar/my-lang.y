%{
    #include <stdio.h>
    #include "ast.h"

    int yylex();
    void yyerror(const char *err);

    extern AstStack sourceItems;
%}

%union {
    struct Ast ast;
}

/* statement tokens */
%token IF ELSE WHILE DO BREAK

%token <ast> VARNAME TYPENAME CHAR STRING NUM BOOL
%type <ast> src_item func_signature stmt_block arg_def list_arg_def stmt_block_inner type_ref non_empty_list_arg_def stmt arr_size_def list_init_var init_var if_stmt expr literal list_expr non_empty_list_expr 

%right '='

%left '-' '+'
%left '*' '/'

%left '[' '('

%%

src
    : /* empty */ 
    | src_item src { pushToAstStack(&sourceItems, $1); }
;

src_item
    : func_signature ';' { $$ = createAstNode(NT_FUNC, 1, $1); }
    | func_signature stmt_block { $$ = createAstNode(NT_FUNC, 2, $1, $2); }
;

func_signature
    : arg_def '(' list_arg_def ')' { $$ = createAstNode(NT_FUNC_SIGNATURE, 2, $1, $3); }
;

arg_def
    : VARNAME { $$ = $1; }
    | type_ref VARNAME { $$ = createAstNode(NT_ARG_DEF, 2, $1, $2); } 
;

list_arg_def
    : /* empty */ { $$ = createAstNode(NT_ARG_DEF_LIST, 0); }
    | non_empty_list_arg_def { $$ = $1; }
;

non_empty_list_arg_def
    : arg_def { $$ = $1; }
    | arg_def ',' non_empty_list_arg_def { $$ = createAstNode(NT_ARG_DEF_LIST, 2, $1, $3); }
;

stmt_block
    : '{' stmt_block_inner '}' { $$ = $2; }
;

stmt_block_inner
    : /* empty */ { $$ = createAstNode(NT_STMT_BLOCK_INNER, 0); }
    | stmt stmt_block_inner { $$ = createAstNode(NT_STMT_BLOCK_INNER, 2, $1, $2); }
;

stmt
    : type_ref list_init_var ';' { $$ = createAstNode(NT_INIT_VAR_STMT, 2, $1, $2); }
    | if_stmt { $$ = $1; }
    | stmt_block { $$ = $1; }
    | WHILE '(' expr ')' stmt { $$ = createAstNode(NT_WHILE_STMT, 2, $3, $5); }
    | DO stmt_block WHILE '(' expr ')' ';' { $$ = createAstNode(NT_DO_WHILE_STMT, 2, $2, $5); }
    | BREAK ';' { $$ = createAstNode(NT_BREAK_STMT, 0); }
    | expr ';' { $$ = $1; }
;

type_ref
    : TYPENAME { $$ = $1; }
    | type_ref '[' arr_size_def ']' { $$ = createAstNode(NT_TYPE_REF, 2, $1, $3); }
;

arr_size_def
    : /* empty */ { $$ = createAstNode(NT_ARR_SIZE_DEF_LIST, 0); }
    | ',' arr_size_def { $$ = createAstNode(NT_ARR_SIZE_DEF_LIST, 1, $2); }
;

list_init_var
    : init_var { $$ = $1; }
    | init_var ',' list_init_var { $$ = createAstNode(NT_INIT_VAR_LIST, 2, $1, $3); }
;

init_var
    : VARNAME { $$ = $1; }
    | VARNAME '=' expr { $$ = createAstNode(NT_INIT_VAR_STMT, 2, $1, $3); }
;

if_stmt
    : IF '(' expr ')' stmt { $$ = createAstNode(NT_IF_STMT, 2, $3, $5); }
    | IF '(' expr ')' stmt ELSE stmt { $$ = createAstNode(NT_IF_ELSE_STMT, 3, $3, $5, $7); }
;

expr
    : literal { $$ = $1; }
    | VARNAME { $$ = $1; }

    | expr '(' list_expr ')' { $$ = createAstNode(NT_CALL_EXPR, 2, $1, $3); }
    | expr '[' list_expr ']' { $$ = createAstNode(NT_INDEX_EXPR, 2, $1, $3); }
    | '(' expr ')' { $$ = $2; }
    | expr '=' expr { $$ = createAstNode(NT_ASSIGN_EXPR, 2, $1, $3); }

    | expr '+' expr { $$ = createAstNode(NT_ADD_EXPR, 2, $1, $3); }
    | expr '-' expr { $$ = createAstNode(NT_SUB_EXPR, 2, $1, $3); }
    | expr '*' expr { $$ = createAstNode(NT_MUL_EXPR, 2, $1, $3); }
    | expr '/' expr { $$ = createAstNode(NT_DIV_EXPR, 2, $1, $3); }
;

literal
    : STRING { $$ = $1; }
    | CHAR { $$ = $1; }
    | NUM { $$ = $1; }
    | BOOL { $$ = $1; }
;

list_expr
    : /* empty */ { $$ = createAstNode(NT_EXPR_LIST, 0); }
    | non_empty_list_expr { $$ = $1; }
;

non_empty_list_expr
    : expr { $$ = $1; }
    | expr ',' non_empty_list_expr { $$ = createAstNode(NT_EXPR_LIST, 2, $1, $3); }
;

%%

void yyerror(const char *err) {
	fprintf(stderr, "error: %s\n", err);
}
