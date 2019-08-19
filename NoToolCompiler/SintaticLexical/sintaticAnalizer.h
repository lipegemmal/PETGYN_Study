#include "lexicalAnalizer.h"
#include "token.h"
#include "libTypes.h"



class SINTATIC{

    public:
        char precedence(TOKEN t);
        TOKEN getTop(){return pile.top();};
        bool isEmpty(){return pile.empty();};
        int getPrecPos(char c) { return precedences[0].find(c); };
        char getPrecedence(int line, int column){return precedences[line][column];};
        SINTATIC(std::string s);
        ~SINTATIC();

        void cabecalho();
        void expressao();

    private:
        std::stack<TOKEN> pile;
        std::string s;
        LEXER* lex;


       
        void empileToken(TOKEN t ){pile.push(t);};
        void emptyPile(){while(!pile.empty()){pile.pop();}};
        void popPile(){pile.pop();};
        
        //compares TOKEN t precedence with pile.top()'s token
        //char precedence(TOKEN t);

        //Error function
        void errorExit(Error e,std::string s)
        {
            switch (e)
            {
            case Error::Overflow:
                std::cout << "Overflow";
                break;
            case Error::UnknownSimbol:
                std::cout << "UnknownSimbol";
                break;
            case Error::NonIdentifier:
                std::cout << "NonIdentifier";
                break;
            case Error::NonAtribuition:
                std::cout << "NonAtribuition";
                break;
            case Error::Empty:
                std::cout << "Empty";
                break;
            }
            std::cout <<" Error In :"<< s <<std::endl;
            exit(1);
        }
};


