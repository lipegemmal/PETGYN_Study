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
\-                  { return '-'; }
\,                  { return ','; }
\=                  { return '='; }
[\n]                { return '\n'; }
("PI"|"pi")         { return PI; }
("EULER"|"euler")   { return EULER;}
("log"|"log2"|"log10") { return LOG; }
("LN"|"ln")         { return LN; }
("pow")             {return POW; }
("fabs")            { return ABS; }
("sqrt")            { return SQRT; }
[0-9]+([.][0-9]*)?([e]([-]|[+])?[0-9]*)? { yylval.str = strdup(yytext) ; return NUMBER;} 
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = strdup(yytext); return VAR;}
[ \t]*              { }
.                   { printf("What is this: %s.\n", yytext); }
%%
