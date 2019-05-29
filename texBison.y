

%{

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "texLexer.h"

extern int yyparse();
extern int yylex();
void yyerror(char **result,const char *s);

%}

%parse-param { char **result }

%union{
    double d;
    char *str;
}


%token <str> NUMBER
%token <str> VAR
%token <str> PI EULER
%token <str> SIN COS TAN
%token <str> ASIN ACOS ATAN
%token <str> SINH COSH TANH
%token <str> LOG LN
%token <str> ABS SQRT
%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation */
%token '\n'
%type <str>  exp
%type <str> trigfunc
%type <str> cabecalho 
/* Grammar follows */

%%

calc:  
|cabecalho '=' exp '\n'  { 
    char c[1024];
    sprintf(c,"%s = %s",$1,$3);
    *result = strdup(c); 
    printf("Resultado dentro do bison: %s e %s\n",$1,$3);
    free($1);
    free($3);
}
;

cabecalho: VAR{ $$ = $1;}
;

exp: VAR { 
       //char *c = strdup($1);
        $$ = $1;
}

    | NUMBER { 
        char c[24]; 
        sprintf(c,"\\num{%s}",$1);   
        $$ = strdup(c);
        free($1);
    }

    | PI{
        //M_PI
        char c[10];
        sprintf(c,"3.14");
        $$ = strdup(c);
    }

    | EULER{
        //M_E
        char c[4];
        sprintf(c,"e");
        $$ = strdup(c);
    }

    |trigfunc{
        $$ = $1;
    }
    
    | LOG '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\log{%s}",$3);
        $$ = strdup(c);
        free($3);
    }

    | LN '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\ln{%s}",$3);
        $$ = strdup(c);
        free($3);
    }

    | ABS '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\left|\\left|%s\\right|\\right|",$3);
        $$ =strdup(c);
        free($3);
    }

    | SQRT '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\sqrt{%s}",$3);
        $$ = strdup(c);
        free($3);
    } 

    | exp '+' exp 
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"%s+%s",$1,$3);
        $$ = strdup(c);
        free($1);
        free($3);
    }

    | exp '-' exp
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof('-')*sizeof($3))+1 );
        
        sprintf(c,"%s-%s",$1,$3);
        $$ = strdup(c);
        free($1);
        free($3);
    }

    | exp '*' exp
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof("\\ast")*sizeof($3))+1 );
        
        sprintf(c,"%s\\cdot %s",$1,$3);
        $$ = strdup(c);
        free($1);
        free($3);

    }
    
    | exp '/' exp
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof("\\frac{}{}")*sizeof($3)+1 );
        
        sprintf(c,"\\left(\\frac{%s}{%s}\\right)",$1,$3);
        $$ = strdup(c);
        // string = \frac{%1}{%3}
        free($1);
        free($3);
    }

    | '-' exp
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"-%s",$2);
        $$ = strdup(c);
        free($2);
    }

    | exp '^' exp
    {
         char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"%s^{%s}",$1,$3);
        $$ = strdup(c);
        free($1);
        free($3);
    }

    | '(' exp ')' 
    {
        char c[1024];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"\\left(%s\\right)",$2);
        $$ = strdup(c);
        free($2);
    }

;

trigfunc: 
    SIN '(' exp ')'
    {
        char c[1024];

        sprintf(c,"\\sin{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }
    
    | COS '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\cos{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }

    | TAN '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\tan{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }
    
    | ASIN '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\asin{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }

    | ACOS '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\acos{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }

    | ATAN '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\atan{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }

    | SINH '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\sinh{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }

    | COSH '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\cosh{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }
    
    | TANH '(' exp ')'
    {
        char c[1024];
        sprintf(c,"\\tanh{(%s)}",$3);
        $$ = strdup(c);
        free($3);
    }
;
%%

//To execute without main.c, uncomment bison main()
/*
int main(int argc, char **argv){

    yyparse();
    return 0;
}
*/
void yyerror(char **result , const char *s) {
  printf("EEK, parse error!  Message: %s Result: %s\n",s,*result);
  // might as well halt now:
  exit(-1);
}