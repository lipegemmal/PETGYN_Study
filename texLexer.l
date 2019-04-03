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
\/                  { return '/'; } //\frac{}
\*                  { return '*'; } // \ast 
\^                  { return '^'; }
\-                  { return '-'; }
[\n]                { return '\n'; }
[0-9]+(['.'][0-9]*)? { yylval.str = strdup(yytext) ; return NUMBER;} 
[a-zA-Z][a-z0-9]?    { yylval.str = strdup(yytext); return VAR;}
[ \t]*              { }
.                   { printf("What is this: %s.\n", yytext); }

%%
