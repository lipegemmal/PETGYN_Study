/* Infix notation calculator--calc */

%{
//#define YYSTYPE double

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();

void yyerror(const char *s);

%}

%union{
    double d;
}


/* BISON Declarations */
%token <d> NUMBER
%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation        */
%token '\n'

%type <d>  exp 
/* Grammar follows */

%%

calc:  
|exp '\n'  {printf(" = %f\n", $1); fflush(stdout);return;}
;
    
exp:      NUMBER             { $$ = $1;         }
        | exp '+' exp        { $$ = $1 + $3;    }
        | exp '-' exp        { $$ = $1 - $3;    }
        | exp '*' exp        { $$ = $1 * $3;    }
        | exp '/' exp        { $$ = $1 / $3;    }
        | '-' exp            { $$ = -$2;        }
        | exp '^' exp        { $$ = pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }

;
%%

int main(int argc, char **argv){

    yyparse();
    return 0;
}

void yyerror(const char *s) {
  printf("EEK, parse error!  Message: %s\n",s);
  // might as well halt now:
  exit(-1);
}