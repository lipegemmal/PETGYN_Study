/* =======================================================================
    Funcao: main                                                 05/08/90

    Modulo de teste do ANALEX do Gerador de Codigo p/ Funcoes Matematicas
   ======================================================================= */

#include <stdio.h>
#include "ANAEXPR.h"

int ANALEX(char*, double*, char*);
int PESQRES(char *);
int ISVALID(char );
int ISSIMB(char );

void strset(char *, char);

int main()
{
  char   atomo[T_IDENT];
  char   classe = 0;
  double valor  = 0;

  erro = ind = simbant = 0;

  printf("\n EXPRESSAO ==> ");
  gets(funcao);
  while (classe != CL_FIM && !erro)
   { ANALEX(&classe,&valor,atomo);
     printf("\n ==> classe - %d, atomo - %5s, valor - %f",classe,atomo,valor);
   }
  if (erro)
    printf("\n Erro ==> %d",erro);

  return 0;
}


/* ======================================================================
    Funcao: ANALEX                                              20/08/90

    Faz a analise lexica da expressao a ser compilada

    Param out: classe - classe do atomo
	       valor  - valor numerico na forma interna
	       atomo  - identificador
   ======================================================================= */
int ANALEX(char *classe, double *valor, char *atomo)
{

 
  void S1(char *classe);
  void S2(void);
  void S3(double *valor);
  void S4(char *classe, char *atomo);
  void S5(char *classe, char *atomo);
  void S6(char *atomo);
  void S7(char *atomo);
  void S8(char *classe, char *atomo);
  void S9(char *classe);

    strset(atomo, 0); /* inicializa o atomo com 0's       */
    *classe = *valor = 0;

  A0:                                  /* Estado inicial do Automato       */
      if (funcao[ind] == '\0')
       { *classe = CL_FIM;
         goto A8;
       }
      else
	      if (isspace(funcao[ind]))
        { ++ind;
          goto A0;
        }
        else
          if (isdigit(funcao[ind]))
          { S1(classe);
            goto A1;
          }
          else
            if (funcao[ind] == '.')
            { S1(classe);
               goto A2;
            }
            else
              if (funcao[ind] == '+' || funcao[ind] == '-')
	              { S5(classe,atomo);
                 goto A8;
                }
              else
                if (isalpha(funcao[ind]))
                 { S6(atomo);
                   goto A6;
                 }
                else
		              if (ISVALID(funcao[ind]))
		              { S6(atomo);
		                goto A7;
		              }
                  else
		                return(erro = ER_SIMB);
                                       /* caracter desconhecido            */

  A1: ++ind;
      if (isdigit(funcao[ind]))
       { S2();
         goto A1;
       }
      else
        if (funcao[ind] == '.')
	      { S2();
	        goto A4;
	      }
        else
          if (funcao[ind] == 'E' || funcao[ind] == 'e')
           { S2();
             goto A3;
           }
          else
            if (ISVALID(funcao[ind]))
             { S3(valor);
               goto A8;
             }
            else
              return(erro = ER_SIMB);

  A2: ++ind;
      if (isdigit(funcao[ind]))
       { S2();
         goto A4;
       }
      else
        if (ISVALID(funcao[ind]))
         { S4(classe,atomo);
           goto A8;
         }
        else
          return(erro = ER_SIMB);

  A3: ++ind;
      if (isdigit(funcao[ind]) || funcao[ind] == '+' || funcao[ind] == '-')
       { S2();
         goto A5;
       }
      else
        return(erro = ER_SIMB);

  A4: ++ind;
      if (isdigit(funcao[ind]))
       { S2();
         goto A4;
       }
      else
        if (funcao[ind] == 'E' || funcao[ind] == 'e')
         { S2();
           goto A3;
         }
        else
          if (ISVALID(funcao[ind]))
           { S3(valor);
             goto A8;
           }
          else
            return(erro = ER_SIMB);

  A5: ++ind;
      if (isdigit(funcao[ind]))
       { S2();
         goto A5;
       }
      else
        if (ISVALID(funcao[ind]))
         { S3(valor);
           goto A8;
         }
        else
          return(erro = ER_SIMB);

  A6: ++ind;                           /* Estado que trata identificadores */
      if (isalnum(funcao[ind]))
       { S7(atomo);
         goto A6;
       }
      else
	      if (ISSIMB(funcao[ind]) || isspace(funcao[ind]))
	      { S8(classe,atomo);
          goto A8;
        }
        else
          return(erro = ER_SIMB);

  A7: ++ind;                           /* Estado que trata simb. especiais */
      if (ISVALID(funcao[ind]))
       { S9(classe);
         goto A8;
       }
      else
        return(erro = ER_SIMB);

  A8:                                  /* Estado final do Automato         */
      simbant = funcao[ind-1];
      return(1);
}





/* =======================================================================
    Funcao: S1 ... S9                                            20/08/90
    Rotinas semanticas do analisador lexico
   ======================================================================= */


//Inicia a leitura de um número
void S1(char *classe)
{
  strset(numero,0);
  *classe = CL_NUM;
  simbant = pos = 0;
  numero[pos] = funcao[ind];
}

//recebe um digito
void S2(void)
{
  numero[++pos] = funcao[ind];
}


void S3(double *valor)
{
  *valor = atof(numero);
  if (*valor == 0)
    erro = ER_OVER;
}


void S4(char *classe,char *atomo)
{
  *classe = CL_SIMB;
  atomo[pos] = numero[pos];
}


void S5(char *classe,char *atomo)
{
  *classe = CL_SIMB;
  if (strchr(PRE_UNARIO,simbant))
    if (funcao[ind] == '-')
      atomo[0] = '!';
    else
      atomo[0] = '?';
  else
    atomo[0] = funcao[ind];
  simbant = funcao[ind];
  ++ind;
}


void S6(char *atomo)
{
  pos = 0;
  atomo[pos] = funcao[ind];
  if (strchr(PRE_UNARIO,funcao[ind]))
    simbant = funcao[ind];
  else
    simbant = 0;
}


void S7(char *atomo)
{
  if (pos < (T_IDENT - 2))
    atomo[++pos] = funcao[ind];
}


void S8(char *classe, char *atomo)
{
  if (PESQRES(atomo))
    *classe = CL_RES;
  else
    *classe = CL_IDEN;
}


void S9(char *classe)
{
  *classe = CL_SIMB;
}





/* =======================================================================
    Funcao: PESQRES                                              20/08/90
    Realiza pesquisa binaria do atomo na tabela de palavras reservadas

    Param in:  arg    - argumento de pesquisa

    Param out:  0  ===> nao foi encontrado o argumento
		1  ===> o argumento de pesquisa foi encontrado
   ======================================================================= */

int PESQRES(char *arg)
{
  int primeiro, ultimo, medio, pesq;

  primeiro = 0;
  ultimo = NUM_RES - 1;

  while (primeiro <= ultimo)
   { medio = (ultimo + primeiro) / 2;
     pesq = strcmp(arg,tbres[medio]);
     if (pesq == 0)                    /* pesquisa bem sucedida            */
       return(1);
     if (pesq < 0)
       ultimo = medio - 1;
     else
       primeiro = medio + 1;
   }

  return(0);                           /* pesquisa mal sucedida            */
}




/* =======================================================================
    Funcao: ISVALID                                              20/08/90
    Verifica se um caracter da funcao eh valido

    Param in:   c - caracter a verificar
    Param out:  1 ===> o caracter eh valido
		0 ===> o caracter nao eh valido
   ======================================================================= */

int ISVALID(char c)
{
  if (isalnum(c) || ISSIMB(c) || isspace(c))
    return(1);
  return(0);
}



/* =======================================================================
    Funcao: ISSIMB                                               20/08/90
    Verifica se um caracter da funcao eh um simbolo especial

    Param in:   c - caracter a verificar
    Param out:  1 ===> o caracter eh simbolo especial
		0 ===> o caracter nao eh simbolo especial
   ======================================================================= */

int ISSIMB(char c)
{
  if (strchr(CAR_ESPEC,c) != NULL)
    return(1);
  return(0);
}

void strset(char *str, char c){
  memset(str,c, strlen(str) );
}