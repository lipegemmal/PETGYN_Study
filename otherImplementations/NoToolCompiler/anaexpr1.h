#include "ctype.h"
#include "stdlib.h"
#include "string.h"

#define NULL         0

#define CL_IDEN      1 	               /* identificador                     */
#define CL_FUNC      2                 /* funcao pre-definida               */
#define CL_CONS      3                 /* constante                         */
#define CL_NUM       4                 /* numero                            */
#define CL_SIMB      5 	               /* simbolo especial                  */
#define CL_FIM       6 	               /* fim de arquivo                    */

#define POS_FUNC     11                /* posicao de funcao na tab. prec.   */
#define POS_IDEN     12                /* posicao de ident. na tab. prec.   */
#define POS_CONS     13                /* posicao de const. na tab. prec.   */
#define POS_NUM      13                /* posicao de numero na tab. prec.   */

#define ER_SIMB      1                 /* erro - simbolo desconhecido       */
#define ER_OVER      2                 /* erro - overflow                   */
#define ER_IDEN      3                 /* identificador esperado            */
#define ER_VAR       4                 /* excesso de variaveis na funcao    */
#define ER_CAB       5                 /* , ou ) esperado na lista de var.  */
#define ER_ATRIB     6                 /* = esperado apos o cabecalho       */
#define ER_EXPR      7                 /* expressao invalida                */

#define CAR_ESPEC    ".,=()^*/+-"      /* caracteres especiais              */
#define PRE_UNARIO   "=,(^*/+-"        /* car. que antecedem um op. unario  */

#define T_IDENT      6                 /* tamanho de identificadores        */
#define T_EXPR       80                /* tamanho maximo da expressao       */
#define T_NUM        23                /* tamanho maximo de um numero       */
#define NUM_VAR      3                 /* nr. maximo de variaveis na funcao */
#define NUM_SIMB     10                /* numero de simbolos especiais      */
#define NUM_RES      16                /* numero de palavras reservadas     */
#define NUM_OPER     14                /* numero de operadores              */

struct dados {char   classe;           /* estrutura da pilha sintatica      */
              double valor;
              char   atomo[T_IDENT];
              struct dados *proximo;
             };

struct dados *pt_topo = NULL;          /* ponteiro para a pilha sintatica   */

int  ind;
int  erro;
char simbant;
char *pt_funcao;
char *pt_numero;
char numero[T_NUM];

static char *pal_res[] = {"ABS",        /* tabela de palavras reservadas    */
                          "ACOS",
                          "ASEN",
                          "ATAN",
                          "COS",
                          "COSH",
                          "EXP",
                          "LN",
                          "LOG",
                          "SEN",
                          "SENH",
                          "SQRT",
                          "TAN",
                          "TANH",
                          "NEP",
                          "PI"};

static char *tab_prec[] = {"#+-*/^!?(),   ",
                           " <<<<<<<<  <<<",  /* #             */
                           ">>><<<<<<> <<<",  /* +             */
                           ">>><<<<<<> <<<",  /* -             */
                           ">>>>><<<<> <<<",  /* *             */
                           ">>>>><<<<> <<<",  /* /             */
                           ">>>>><<<<> <<<",  /* ^             */
                           ">>>>>>  <> <<<",  /* !             */
                           ">>>>>>  <> <<<",  /* ?             */
                           " <<<<<<<<==<<<",  /* (             */
                           ">>>>>>>> >>   ",  /* )             */
                           "      <<<==<<<",  /* ,             */
                           ">>>>>>>><>    ",  /* funcao        */
                           ">>>>>>>>=>>   ",  /* identificador */
                           ">>>>>>>> >>   "}; /* constante     */

int  CABECALHO(struct dados *pt_param);
int  EXPRESSAO(struct dados *pt_param);
int  INSERE_PILHA(struct dados *pt_param);
int  RETIRA_PILHA(struct dados *pt_alavanca);
int  PRECEDENCIA(struct dados *pt_dados);
int  INDTAB(char ch);
int  ANALEX(struct dados *pt_param);
int  PESQFUNC(char arg[]);
int  ISVALID(char c);
int  ISSIMB(char c);
int  GETCH(void);
void S1(struct dados *pt_param, char c);
void S2(char c);
void S3(struct dados *pt_param);
void S4(struct dados *pt_param, char c);
void S5(struct dados *pt_param, char c);
void S6(struct dados *pt_param, char c);
void S7(struct dados *pt_param);
void S8(struct dados *pt_param);

