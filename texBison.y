

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
%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation */
%token '\n'
%type <str>  exp 
/* Grammar follows */

%%

calc:  
|exp '\n'  { *result = strdup($1); printf("Resultado dentro do bison: %s\n",*result);}
;
    

exp: VAR { 
       //char *c = strdup($1);
        $$ = strdup($1);
    }
    | NUMBER { $$ = strdup($1);}

    | exp '+' exp 
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"%s+%s",$1,$3);
        $$ = strdup(c);

    }
    | exp '-' exp
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof('-')*sizeof($3))+1 );
        
        sprintf(c,"%s-%s",$1,$3);
        $$ = strdup(c);
    }
    | exp '*' exp
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof("\\ast")*sizeof($3))+1 );
        
        sprintf(c,"%s\\ast%s",$1,$3);
        $$ = strdup(c);
        //string = %1 \ast %3
    }
    
    | exp '/' exp
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof("\\frac{}{}")*sizeof($3)+1 );
        
        sprintf(c,"\\frac{%s}{%s}",$1,$3);
        $$ = strdup(c);
        // string = \frac{%1}{%3}
    }
    | '-' exp
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"-%s",$2);
        $$ = strdup(c);

    }
    | exp '^' exp
    {
         char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"%s^{%s}",$1,$3);
        $$ = strdup(c);

    }
    | '(' exp ')' 
    {
        char c[256];//= malloc( (sizeof(char)*sizeof($1)*sizeof('+')*sizeof($3))+1 );
        
        sprintf(c,"(%s)",$2);
        $$ = strdup(c);


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
  printf("EEK, parse error!  Message: %s\n",s);
  // might as well halt now:
  exit(-1);
}