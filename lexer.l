%{
/*#include <cstdlib>
#include <string>
*/
#include <stdio.h>
#include <stdlib.h>
//enum batata {NUMBER,VAR,CONST};
// enum batata {NUMBER}


#include "t.tab.h"

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
[\n]                { return '\n'; }
[0-9]+(['.'][0-9]*)? { yylval.d = atof(yytext) ; return NUMBER;} 
[ \t]*              { }
.                   { printf("What is this: %s.\n", yytext); }

%%
