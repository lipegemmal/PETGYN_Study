%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texBison.tab.h"

%}

%%
\(                  { return '('; }
\)                  { return ')'; }
\[                  { return '('; }
\]                  { return ')'; }
\+                  { return '+'; }
\/                  { return '/'; } 
\*                  { return '*'; }  
\^                  { return '^'; }
\-                  { return '-'; }
\,                  { return ','; }
\=                  { return '='; }
[\n]                { return '\n'; }
("PI"|"pi")         { return PI; }
e                   { return EULER;}
("SIN"|"sin")       { return SIN; }
("COS"|"cos")       { return COS; }
("TAN"|"tan")       { return TAN; }
("ASIN"|"asin")     { return ASIN; }
("ACOS"|"acos")     { return ACOS; }
("ATAN"|"atan")     { return ATAN; }
("SINH"|"sinh")     { return SINH; }
("COSH"|"cosh")     { return COSH; }
("EXP"|"exp")       { return '^'; }
("NEP"|"nep")       { return EULER; }
("TANH"|"tanh")     { return TANH; }
("LOG"|"log")       { return LOG; }
("LN"|"ln")         { return LN; }
("ABS"|"abs")       { return ABS; }
("SQRT"|"sqrt")     { return SQRT; }
[0-9]+([.][0-9]*)?([eE]([-]|[+])?[0-9]*)? { yylval.str = strdup(yytext) ; return NUMBER;} 
[a-zA-Z][a-zA-Z0-9]*    { yylval.str = strdup(yytext); return VAR;}
[ \t]*              { }
.                   { printf("What is this: %s.\n", yytext); }
%%
