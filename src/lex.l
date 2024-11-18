%{
    // TODO: make rules write ast

    #include "ast.h"
    #include "prs.h"
%}

DIGIT [0-9]
LETTER [a-zA-Z_]
NAME_SYMBOL [a-zA-Z0-9_] 

SPECIAL_SYMBOL [\(\)\,\;\[\]\{\}\+\-\*\/\=]

HEX 0[Xx][a-fA-F0-9]+
BIN 0[Bb][01]+
DEC {DIGIT}+

BUILT_IN_TYPE (bool)|(byte)|(u?(int)|(long))|(char)|(string)

%%

if { return IF; }
else { return ELSE; }
while { return WHILE; }
do { return DO; }
break { return BREAK; }

L?\"(\\.|[^\\"\n])*\" { yylval.ast = createAstToken(yytext); return STRING; }
L?\'(\\.|[^\\'\n])+\' { yylval.ast = createAstToken(yytext); return CHAR; }
{HEX}|{BIN}|{DEC} { yylval.ast = createAstToken(yytext); return NUM; }
(true)|(false) { yylval.ast = createAstToken(yytext); return BOOL; }

{BUILT_IN_TYPE} { yylval.ast = createAstToken(yytext); return TYPENAME; }
{LETTER}{NAME_SYMBOL}* { yylval.ast = createAstToken(yytext); return VARNAME; }

{SPECIAL_SYMBOL} { return *yytext; }

"//"[^\n"]* /* consume comment */
[ \t\n] /* eat up whitespace */

. { return 0; /* unknown symbol */ }

%%