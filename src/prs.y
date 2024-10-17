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

argDef:
    ID
    | typeRef ID
;

listArgDef:
    // nothing
    | argDef
    | listArgDef ',' argDef
;

funcSignature: argDef '(' listArgDef ')';

sourceItem:
    | funcSignature ';'
;

%%