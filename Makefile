batata: texBison.y texLexer.l main.cpp equation.cpp 
	bison -d texBison.y
	flex --header-file=texLexer.h texLexer.l
	g++ equation.cpp main.cpp texBison.tab.c lex.yy.c -lm -lfl -o a.out
