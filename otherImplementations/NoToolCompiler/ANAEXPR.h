#include "ctype.h"
#include "stdlib.h"
#include "string.h"

//#define NULL         0

#define CL_IDEN      1 	               /* identificador                    */
#define CL_RES       2                 /* palavra reservada                */
#define CL_NUM       3                 /* numero                           */
#define CL_SIMB      4 	               /* simbolo especial                 */
#define CL_FIM       5 	               /* fim de arquivo                   */

#define ER_SIMB      1                 /* erro - simbolo desconhecido      */
#define ER_OVER      2                 /* erro - overflow                  */

#define CAR_ESPEC    ".,=()^*/+-"      /* caracteres especiais             */
#define PRE_UNARIO   ",(^*/+-"         /* car. que antecedem um op. unario */
#define NUM_CAR_ESP  10                /* numero de caracteres especiais   */
#define T_IDENT      6                 /* tamanho de identificadores       */

#define T_EXPR       80                /* tamanho maximo da expressao      */
#define NUM_SIMB     10                /* numero de simbolos especiais     */
#define NUM_RES      16                /* numero de palavras reservadas    */

char ind;
char pos;
char erro;
char simbant;
char funcao[T_EXPR];
char numero[T_EXPR];
/* char atomo[T_IDENT]; */

static char *tbres[NUM_RES] =          /* tabela de palavras reservadas    */
	     {"ABS",
	      "ACOS",
	      "ASIN",
	      "ATAN",
	      "COS",
	      "COSH",
	      "EXP",
	      "LN",
	      "LOG",
	      "NEP",
	      "PI",
	      "SIN",
	      "SINH",
	      "SQRT",
	      "TAN",
	      "TANH"};