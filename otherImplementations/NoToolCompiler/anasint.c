#include "anaexpr1.h"

/* =======================================================================
    Funcao: MAIN                                                  20/09/90
    Modulo de teste do Analisador Sintatico do Compilador de Funcoes Mate-
    maticas
   ======================================================================= */
main()
{
  struct dados param;
  char funcao[T_EXPR];

  erro = 0;
  simbant = ' ';
  printf("\nEXPRESSAO ==> ");
  gets(funcao);
  pt_funcao = funcao;
  CABECALHO(&param);
  if (!erro)
    EXPRESSAO(&param);
  if (erro)
    printf("\n Erro ===> %d\n",erro);
}



/* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */




/* =======================================================================
    Funcao: CABECALHO                                             20/09/90
    Faz a analise sintatica da primeira parte da funcao (ate o sinal de a-
    atribuicao).
   ======================================================================= */
int CABECALHO(struct dados *pt_param)
{
  int cont = 0;

  ANALEX(pt_param);
  if (erro)
    return(0);
  if (pt_param->classe != 1)
    return(erro = 3);
  else
    { /* Colocar o nome da funcao na tabela de simbolos */
      ANALEX(pt_param);
      if (erro)
        return(0);
      else
        if (!strcmp(pt_param->atomo,"("))
         { while(strcmp(pt_param->atomo,")"))
            { ANALEX(pt_param);
              /* Colocar o ident. do parametro na tabela de simbolos */
              if (pt_param->classe == 1 )
               { if (++cont > NUM_VAR)
                   return(erro = 4);
               }
              else
                if (!strcmp(pt_param->atomo,",") &&
                    !strcmp(pt_param->atomo,")"))
                  return(erro = 5);
            }
           ANALEX(pt_param);
           if (erro)
             return(0);
         }
      if (!strcmp(pt_param->atomo,"="))
        return(1);
      else
        return(erro = 6);
    }
}


/* =======================================================================
    Funcao: EXPRESSAO                                             20/09/90
    Faz a analise sintatica da segunda parte da funcao (apos o sinal de a-
    atribuicao).
   ======================================================================= */
int EXPRESSAO(struct dados *pt_param)
{
  char   prec;
  struct dados  alavanca;

  printf("\nPOLONESA:\n");
  alavanca.classe   = 5;
  alavanca.valor    = 0;
  alavanca.atomo[0] = '#';
  alavanca.atomo[1] = '\0';
  alavanca.proximo  = NULL;
  INSERE_PILHA(&alavanca);
  simbant = '=';
  ANALEX(pt_param);
  if (erro)
    return(0);
  else
   if (pt_param->classe == CL_FIM)
     return(erro=9);
  while(1)
   { if ((!strcmp(pt_topo->atomo,"#")) &&
         (!strcmp(pt_param->atomo,"#")))
       return(1);
     else
       { prec = PRECEDENCIA(pt_param);
         if (prec == '<' || prec == '=')
          { INSERE_PILHA(pt_param);
            if (pt_param->classe != CL_FIM)
             { ANALEX(pt_param);
               if (erro)
                 return(0);
               else
                 if (pt_param->classe == CL_FIM)
                  { pt_param->atomo[0] = '#';
                    pt_param->atomo[1] = '\0';
                  }
             }
          }
         else
           if (prec == '>')
            { do
               { RETIRA_PILHA(&alavanca);
                 prec = PRECEDENCIA(&alavanca);
                 printf("%s",alavanca.atomo);
               }
              while (prec != '<');
              printf("\n");
            }
            /* geracao de codigo */
           else
             return(erro = 7);
       }
   }
}


/* =======================================================================
    Funcao: INSERE_PILHA                                          20/09/90
    Coloca uma estrutura com os elementos do item lexico no topo da pilha
   ======================================================================= */
int INSERE_PILHA(struct dados *pt_param)
{
  static struct dados *pt_novo;

	if ((pt_novo = malloc(sizeof(struct dados))) == NULL)
    return(erro = 8);
  else
   { *pt_novo         = *pt_param;
     pt_novo->proximo = pt_topo;
     pt_topo          = pt_novo;
     return(1);
   }
}


/* =======================================================================
    Funcao: RETIRA_PILHA                                          20/09/90
    Retira uma estrutura com os elementos do item lexico do topo da pilha
   ======================================================================= */
int RETIRA_PILHA(struct dados *pt_alavanca)
{
  struct dados *pt_aux;

  if (pt_topo == NULL)
    return(1);
  else
   { *pt_alavanca = *pt_topo;
     pt_aux       = pt_topo->proximo;
     free(pt_topo);
     pt_topo      = pt_aux;
     return(1);
   }
}


/* =======================================================================
    Funcao: PRECEDENCIA                                           20/09/90
    Verifica qual a precedencia entre dois operadores da funcao
   ======================================================================= */
int PRECEDENCIA(struct dados *pt_dados)
{
  int aux1,
      aux2;

  switch (pt_topo->classe)
   { case CL_IDEN : aux1 = POS_IDEN; break;
     case CL_FUNC : aux1 = POS_FUNC; break;
     case CL_CONS : aux1 = POS_CONS; break;
     case CL_NUM  : aux1 = POS_NUM;  break;
     case CL_SIMB : aux1 = INDTAB(pt_topo->atomo[0]);
   }
  switch (pt_dados->classe)
   { case CL_IDEN : aux2 = POS_IDEN; break;
     case CL_FUNC : aux2 = POS_FUNC; break;
     case CL_CONS : aux2 = POS_CONS; break;
     case CL_NUM  : aux2 = POS_NUM;  break;
     case CL_SIMB : aux2 = INDTAB(pt_dados->atomo[0]); break;
     case CL_FIM  : aux2 = INDTAB(pt_dados->atomo[0]);
   }
  return((char)tab_prec[aux1+1][aux2]);
}


/* =======================================================================
    Funcao: INDTAB                                                20/09/90
    Verifica qual a posicao de um operador na tabela de precedencia
   ======================================================================= */
int INDTAB(char ch)
{
  int ind = -1;

  while (++ind <= NUM_OPER)
   { if (tab_prec[0][ind] == ch)
       return(ind);
   }
  return(0);
}



/* *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */



/* ======================================================================
    Funcao: ANALEX                                               20/08/90

    Faz a analise lexica da expressao a ser compilada

    Param out: classe - classe do atomo
               valor  - valor numerico na forma interna
               atomo  - identificador
   ======================================================================= */
int ANALEX(struct dados *pt_param)
{
  int  estado = 0;
  char ch = 0;

  pt_param->atomo[0] = '\0';            /* inicializa o atomo com 0's       */
  pt_param->classe   = pt_param->valor = 0;
  pt_param->proximo  = NULL;
  pt_numero          = numero;

  while(1)
   { switch (estado)
      { case 0:                        /* Estado inicial do Automato	   */
                ch = GETCH();
                if (ch == '\0')
                 { pt_param->classe = CL_FIM;
                   estado = 8;
                 }
                else
                  if (isspace(ch))
                    estado = 0;
                  else
                    if (isdigit(ch))
                     { S1(pt_param,ch);
                       estado = 1;
                     }
                    else
                     if (ch == '.')
                      { S1(pt_param,ch);
                        estado = 2;
                      }
                     else
                       if (ch == '+' || ch == '-')
                        { S4(pt_param,ch);
                          estado = 8;
                        }
                       else
                         if (isalpha(ch))
                          { S5(pt_param,ch);
                            estado = 6;
                          }
                         else
                           if (ISVALID(ch))
                            { S5(pt_param,ch);
                              estado = 7;
                            }
                           else
                             return(erro = ER_SIMB);
                break;

        case 1:
                ch = GETCH();
                if (isdigit(ch))
                 { S2(ch);
                   estado = 1;
                 }
                else
                  if (ch == '.')
                   { S2(ch);
                     estado = 3;
                   }
                  else
                    if (ch == 'E' || ch == 'e')
                     { S2(ch);
                       estado = 4;
                     }
                    else
                      if (ISVALID(ch))
                       { S3(pt_param);
                         estado = 8;
                       }
                      else
                        return(erro = ER_SIMB);
                break;

        case 2:
                ch = GETCH();
       	        if (isdigit(ch))
                 { S2(ch);
                   estado = 3;
                 }
                else
                  return(erro = ER_SIMB);
                break;

        case 3:
                ch = GETCH();
                if (isdigit(ch))
                 { S2(ch);
                   estado = 3;
                 }
                else
                  if (ch == 'E' || ch == 'e')
                   { S2(ch);
                     estado = 4;
                   }
                  else
                    if (ISVALID(ch))
                     { S3(pt_param);
                       estado = 8;
                     }
                    else
                      return(erro = ER_SIMB);
                break;

        case 4:
                ch = GETCH();
                if (isdigit(ch) || ch == '+' || ch == '-')
                 { S2(ch);
                   estado = 5;
                 }
                else
                  return(erro = ER_SIMB);
                break;

        case 5:
                ch = GETCH();
                if (isdigit(ch))
                 { S2(ch);
                   estado = 5;
                 }
                else
                  if (ISVALID(ch))
                   { S3(pt_param);
                     estado = 8;
                   }
                  else
                    return(erro = ER_SIMB);
                break;

        case 6:                /* Estado que trata identificadores */
                ch = GETCH();
                if (isalnum(ch))
                 { S6(pt_param,ch);
                   estado = 6;
                 }
                else
                  if (ISSIMB(ch) || isspace(ch))
                   { S7(pt_param);
                     estado = 8;
                   }
                  else
                    return(erro = ER_SIMB);
                break;

        case 7:                /* Estado que trata simb. especiais */
                ch = GETCH();
                if (ISVALID(ch))
                 { S8(pt_param);
                   estado = 8;
                 }
                else
                  return(erro = ER_SIMB);
                break;

        case 8:                   /* Estado final do Automato	   */
                *pt_funcao--;
                return(1);
      }
   }
}


/* =======================================================================
    Funcao: S1 ... S8                                             20/08/90
    Rotinas semanticas do analisador lexico
   ======================================================================= */

void S1(struct dados *pt_param,char c)
{
  pt_param->classe = CL_NUM;
  simbant = ' ';
  *pt_numero++ = c;
  *pt_numero   = '\0';
}


void S2(char c)
{
  *pt_numero++ = c;
  *pt_numero   = '\0';
}


void S3(struct dados *pt_param)
{
  pt_param->valor = atof(numero);
}


void S4(struct dados *pt_param, char c)
{
  pt_param->classe = CL_SIMB;
  if (strchr(PRE_UNARIO,simbant))
    if (c == '-')
      pt_param->atomo[0] = '!';
    else
      pt_param->atomo[0] = '?';
  else
    pt_param->atomo[0] = c;
  pt_param->atomo[1] = '\0';
  simbant = c;
  *pt_funcao++;
}


void S5(struct dados *pt_param, char c)
{
  pt_param->atomo[ind=0] = c;
  pt_param->atomo[1] = '\0';
  if (strchr(PRE_UNARIO,c))
    simbant = c;
  else
    simbant = ' ';
}


void S6(struct dados *pt_param, char c)
{
  if (ind++ < (T_IDENT - 2))
   { pt_param->atomo[ind]   = c;
     pt_param->atomo[ind+1] = '\0';
   }
}


void S7(struct dados *pt_param)
{
  char aux;

  aux = PESQFUNC(pt_param->atomo);
  if (aux)
    pt_param->classe = CL_FUNC;
  else
    if ((!strcmp(pt_param->atomo,"NEP")) ||
        (!strcmp(pt_param->atomo,"PI")))
      pt_param->classe = CL_CONS;
    else
      pt_param->classe = CL_IDEN;
}


void S8(struct dados *pt_param)
{
  pt_param->classe = CL_SIMB;
}


/* =======================================================================
    Funcao: GETCH                                                 20/08/90
    Retorna um caracter da funcao matematica
   ======================================================================= */

int GETCH(void)
{
  return(*pt_funcao++);
}


/* =======================================================================
    Funcao: PESQFUNC                                              20/08/90
    Realiza pesquisa binaria do atomo na tabela de palavras reservadas

    Param in:  arg    - argumento de pesquisa

    Param out: 0      ===> nao foi encontrado o argumento
               outro  ===> o argumento de pesquisa foi encontrado
   ======================================================================= */

int PESQFUNC(char arg[])
{
  int primeiro, ultimo, medio, pesq;

  primeiro = 0;
  ultimo = NUM_RES - 3;   /* Existem duas constantes na tab. pal. reservadas */

  while (primeiro <= ultimo)
   { medio = (ultimo + primeiro) / 2;
     pesq = stricmp(arg,pal_res[medio]);
     if (pesq == 0)		       /* pesquisa bem sucedida 	   */
       return(1);
     if (pesq < 0)
       ultimo = medio - 1;
     else
       primeiro = medio + 1;
   }
  return(0);			       /* pesquisa mal sucedida 	   */
}


/* =======================================================================
    Funcao: ISVALID						                                    20/08/90
    Verifica se um caracter da funcao eh valido

    Param in:	  c - caracter a verificar
    Param out:	1 ===> o caracter eh valido
                0 ===> o caracter nao eh valido
   ======================================================================= */

int ISVALID(char c)
{
  if (isalnum(c) || ISSIMB(c) || isspace(c))
    return(1);
  return(0);
}


/* =======================================================================
    Funcao: ISSIMB						                                    20/08/90
    Verifica se um caracter da funcao eh um simbolo especial

    Param in:	  c - caracter a verificar
    Param out:	1 ===> o caracter eh simbolo especial
                0 ===> o caracter nao eh simbolo especial
   ======================================================================= */

int ISSIMB(char c)
{
  if (strchr(CAR_ESPEC,c) != NULL)
    return(1);
  return(0);
}
