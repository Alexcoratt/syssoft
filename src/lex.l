%{
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #include "prs.h"

    unsigned long int parseBits(const char *);
%}

%%

true|false {
    yylval.boolv = *yytext == 't';
    return BOOL;
}

bool { return BOOL_T; }
byte { return BYTE_T; }
int { return INT_T; }
uint { return UINT_T; }
long { return LONG_T; }
ulong { return ULONG_T; }
char { return CHAR_T; }
string { return STRING_T; }

if { return IF; }
else { return ELSE; }
while { return WHILE; }
do { return DO; }
break { return BREAK; }

[A-Za-z_][A-Za-z0-9_]* { yylval.strv = yytext; return ID; }

\"[^\"\\]*(?:\\.[^\"\\]*)*\" {
    yylval.strv = yytext + 1;
    *strchr(yylval.strv, '\"') = 0;
    return STR;
}

'[^']' { yylval.charv = yytext[1]; return CHAR; }

0[Xx][A-Fa-f0-9]+ { 
    yylval.numv = strtoul(yytext, NULL, 0);
    return HEX;
}

0[Bb][01]+ {
    yylval.numv = parseBits(yytext + 2);
    return BITS;
}

[0-9]+  { 
    yylval.numv = strtoul(yytext, NULL, 0);
    return DEC;
}

[\(\)\,\;\[\]\{\}\+\-\*\/\=] { return *yytext; }

[ \t\n] /* eat up whitespace */

.   { return 0; } /* unknown character */

%%

unsigned long int parseBits(const char *str) {
    unsigned long int res = 0;
    for (; *str; res = (res << 1) + *str - '0', ++str);
    return res;
}