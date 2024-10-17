%{
    #include <stdio.h>
    #include <stdbool.h>

    int yylex();
    void yyerror(const char *err) {
        fprintf(stderr, "error: %s\n", err);
    }
%}

%union {
    char *strv;
    char charv;
    unsigned long int numv;
    bool boolv;
}

/* built-in typerefs */
%token BOOL_T BYTE_T INT_T UINT_T LONG_T ULONG_T CHAR_T STRING_T

/* statement tokens */
%token IF ELSE WHILE DO BREAK

%token <strv> STR ID
%token <charv> CHAR
%token <numv> HEX BITS DEC
%token <boolv> BOOL

%%

source:
    // empty
    | source sourceItem
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

typeRef:
    builtin_t
    | ID
    | typeRef '[' arrSizeDef ']'
;

arrSizeDef:
    // nothing
    | arrSizeDef ','

funcSignature: argDef '(' listArgDef ')';

argDef:
    ID
    | typeRef ID
;

listArgDef:
    // nothing
    | argDef
    | listArgDef ',' argDef
;

sourceItem:
    | funcSignature ';'
    | funcSignature statementBlock
;

initVar:
    ID
    | ID '=' expr

listInitVar:
    // nothing
    | initVar
    | listInitVar ',' initVar
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

statementIf:
    IF '(' expr ')' statement
    | statementIf ELSE statement
;

statementBlock: '{' statementBlockInner '}';

statementBlockInner:
    // nothing
    | statementBlockInner statement
;

expr:
    literal
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | expr '(' listExpr ')'
    | expr '[' listExpr ']'
    | ID
;

literal: STR | CHAR | HEX | BITS | DEC | BOOL;

listExpr:
    // nothing
    | expr
    | listExpr ',' expr
;

%%