# PETGYN_Study
Bison and Flex that will be used in PETGYN application, 


# To compile solver:
$ bison -d solveBison.y
$ flex --header-file=solveLexer.h solveLexer.l
$ gcc equation.cpp main.cpp texBison.tab.c lex.yy.c -lfl -o a.out

