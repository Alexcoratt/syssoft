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
%token BOOL_T, BYTE_T, INT_T, UINT_T, LONG_T, ULONG_T, CHAR_T, STRING_T

%token <strv> STR ID
%token <charv> CHAR
%token <numv> HEX BITS DEC
%token <boolv> BOOL

%type <numv> expr num

%left '='
%left '+'
%left '*'

%%

input:
    // nothing
    | input expr
    | input literal
;

expr:
    num { $$ = $1; }
    | expr '=' { $$ = $1; printf("res: %lu\n", $1); }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '*' expr { $$ = $1 * $3; }
;

num:
    HEX { $$ = $1; }
    | BITS { $$ = $1; }
    | DEC { $$ = $1; }
;

literal:
    ID { printf("ID: %s\n", $1); }
    | STR { printf("STR: %s\n", $1); }
    | CHAR { printf("CHAR: %c\n", $1); }
    | BOOL { printf("BOOL: %s\n", $1 ? "true" : "false"); }

%%