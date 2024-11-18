%code requires {
    #include <stdio.h>
    #include <stdbool.h>

    #include "syntax_tree.h"

    int yylex();
    void yyerror(const char *err) {
        fprintf(stderr, "error: %s\n", err);
    }
}

%union {
    char *strv;
    char charv;
    long int numv;
    bool boolv;
}

/* built-in typerefs */
%token BOOL_T BYTE_T INT_T UINT_T LONG_T ULONG_T CHAR_T STRING_T

/* statement tokens */
%token IF ELSE WHILE DO BREAK

%token <strv> STR VARNAME
%token <numv> CUSTOM_TYPE
%token <charv> CHAR
%token <numv> HEX BITS DEC
%token <boolv> BOOL

%left '-' '+'
%left '*' '/'

%left '[' '('

%%

source:
    // nothing
    | source sourceItem
;

sourceItem:
    funcSignature ';'
    | funcSignature statementBlock
;

funcSignature: argDef '(' listArgDef ')';

argDef:
    VARNAME
    | typeRef VARNAME
;

typeRef:
    builtin_t
    | CUSTOM_TYPE
    | typeRef '[' arrSizeDef ']'
;

builtin_t: 
    BOOL_T
    | BYTE_T
    | INT_T
    | UINT_T
    | LONG_T
    | ULONG_T
    | CHAR_T
    | STRING_T
;

arrSizeDef:
    // nothing
    | arrSizeDef ','

listArgDef:
    // nothing
    | argDef
    | listArgDef ',' argDef
;

statementBlock: '{' statementBlockInner '}';

statementBlockInner:
    // nothing
    | statementBlockInner statement
;

statement:
    typeRef listInitVar ';' 
    | statementIf
    | statementBlock
    | WHILE '(' expr ')' statement
    | DO statementBlock WHILE '(' expr ')' ';'
    | BREAK ';'
    | expr ';'
;

listInitVar:
    initVar
    | listInitVar ',' initVar
;

initVar:
    VARNAME
    | VARNAME '=' expr

statementIf:
    IF '(' expr ')' statement
    | statementIf ELSE statement
;

expr:
    literal
    | VARNAME

    | expr '(' listExpr ')'
    | expr '[' listExpr ']'
    | '(' expr ')'

    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
;

literal: STR | CHAR | HEX | BITS | DEC | BOOL;

listExpr:
    // nothing
    | expr
    | listExpr ',' expr
;

%%

int main(int argc, char **argv) {
    yyparse();

    return 0;
}