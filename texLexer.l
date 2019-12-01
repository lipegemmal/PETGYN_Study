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
("EXP"|"exp")       { return '^'; }
("NEP"|"nep")       { return EULER; }
("LOG"|"log")       { return LOG; }
("LN"|"ln")         { return LN; }
("pow"|"POW")       {return POW; }
("ABS"|"abs")       { return ABS; }
("SQRT"|"sqrt")     { return SQRT; }
[0-9]+([.][0-9]*)?([eE]([-]|[+])?[0-9]*)? { yylval.str = strdup(yytext) ; return NUMBER;} 
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = strdup(yytext); return VAR;}
[ \t]*              { }
.                   { printf("What is this: %s.\n", yytext); }
%%
