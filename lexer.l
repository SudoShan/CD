
%{
#include "y.tab.h"
#include <string.h>
%}

%option noyywrap

%%
"int"       { return INT; }
"float"     { return FLOAT; }
"char"      { return CHAR; }
"double"    { return DOUBLE; }

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"do"        { return DO; }
"continue"  { return CONTINUE; }
"break"     { return BREAK; }

">="        { return GE; }
"<="        { return LE; }
"!="        { return NE; }
"=="        { return EQ; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }

"+="        { return ADD_ASSIGN; }
"-="        { return SUB_ASSIGN; }
"*="        { return MUL_ASSIGN; }
"/="        { return DIV_ASSIGN; }
"++"        { return INC; }
"--"        { return DEC; }

[a-zA-Z_][a-zA-Z0-9_]* {
    strncpy(yylval.str, yytext, 19);
    yylval.str[19] = '\0';
    return ID;
}

[0-9]+ {
    strncpy(yylval.str, yytext, 19);
    yylval.str[19] = '\0';
    return NUM;
}

[ \t\r\n]+    { /* Ignore whitespace */ }

[=<>+\-*/%(){};,] { return yytext[0]; }

. { return yytext[0]; }
%%