batata: texBison.y texLexer.l main.cpp equationManager.cpp  lexicalAnalizer.cpp  sintaticAnalizer.cpp 
	bison -d texBison.y
	flex --header-file=texLexer.h texLexer.l
	g++ equationManager.cpp main.cpp texBison.tab.c lex.yy.c  lexicalAnalizer.cpp  sintaticAnalizer.cpp  -ggdb -std=c++11 -lm -lfl -g -o a.out
