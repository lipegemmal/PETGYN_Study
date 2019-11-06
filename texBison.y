
%{

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sintaticAnalizer.h"
#include "texLexer.h"

//extern int yyparse();
extern int yylex();
void yyerror(char **result, SINTATIC *sintatic,const char *s);
//void yyerror( SINTATIC *sintatic,const char *s);

%}

%parse-param { char **result} { class SINTATIC *sintatic}

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
%type <str> variaveis
%type <str> vars
/* Grammar follows */

%%

calc:  
|cabecalho variaveis '=' exp '\n'  { 
    char c[1024];
    sprintf(c,"%s (%s) = %s",$1,$2,$4);
    *result = strdup(c); 
    printf("Resultado dentro do bison: %s e %s e %s\n",$1,$2,$4);
    

    free($1);
    free($2);
    free($4);
}
;

cabecalho: VAR{ 
    $$ = $1;

    sintatic->setEquationName($1);
    //std::cout << "In Bison EqName:" << sintatic->getName() <<std::endl;

}
;

variaveis: {   
    char c[2];
    sprintf(c," ");
    $$ = strdup(c);
    }
    
    |'('vars')' {
        char c[24];
        sprintf(c,"%s",$2);
        $$ = strdup(c);
        free($2);

    }
;

vars: VAR','vars {
    char c[1024];
    sprintf(c,"%s,%s",$1,$3);
    $$ = strdup(c);
    free($3);

    sintatic->insertVariableList($1);

    }

|VAR {
    $$ = $1;

    sintatic->insertVariableList($1);
}
;


exp: VAR { 
       //char *c = strdup($1);
        $$ = $1;

        if(!sintatic->isInList($1)){
            std::cout<<"Variavel " << $1 << " não está declarada" <<std::endl;           
        };
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
%%

//To execute without main.c, uncomment bison main()
/*
int main(int argc, char **argv){

    yyparse();
    return 0;
}
*/
void yyerror(char **result, SINTATIC *sintatic ,const char *s) {
  printf("EEK, parse error on testBison!  Message: %s \n",s);
  // might as well halt now:
  exit(-1);
}