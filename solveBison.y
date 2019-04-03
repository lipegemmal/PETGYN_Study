

%{

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "solveLexer.h"

extern int yyparse();
extern int yylex();
void yyerror(double *result,const char *s);

%}

%parse-param { double *result }

%union{
    double d;
}


%token <d> NUMBER
%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation */
%token '\n'

%type <d>  exp 
/* Grammar follows */

%%

calc:  
|exp '\n'  { *result = $1;}
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

//To execute without main.c, uncomment bison main()
/*
int main(int argc, char **argv){

    yyparse();
    return 0;
}
*/
void yyerror(double *result , const char *s) {
  printf("EEK, parse error!  Message: %s\n",s);
  // might as well halt now:
  exit(-1);
}