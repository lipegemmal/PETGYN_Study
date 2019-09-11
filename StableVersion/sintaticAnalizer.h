#include "lexicalAnalizer.h"
#include "token.h"
#include "libTypes.h"
#include <utility>


class SINTATIC{

    public:
        char precedence(TOKEN t);
        TOKEN getTop(){return pile.top();};
        bool isEmpty(){return pile.empty();};
        int getPrecPos(char c) { return precedences[0].find(c); };
        char getPrecedence(int line, int column){return precedences[line][column];};
        std::string getName(){return equationName;};
        std::string getExpression(){return expression;};
        SINTATIC(std::string s);
        ~SINTATIC();

        bool isVariableListEmpty(){return variableList.empty();};
        int countVariableList(){return variableList.size();};
       
        std::string getVariableName(int pos){return variableList[pos];};
        std::vector<std::string> getVariableList(){return variableList;};

        void cabecalho();
        void expressao();

    private:
        std::stack<TOKEN> pile;
        std::string s;
        std::string expression;
        LEXER* lex;
        std::string equationName;
        std::vector< std::string > variableList;

        bool isInList(std::string s);
        void emptyVariableList(){variableList.clear();}
        //inserts Variable without value in list;
        void insertVariableList(std::string s){variableList.push_back( s);};
        void empileToken(TOKEN t ){pile.push(t);};
        void emptyPile(){while(!pile.empty()){pile.pop();}};
        void popPile(){pile.pop();};
        //compares TOKEN t precedence with pile.top()'s token
        //char precedence(TOKEN t);
        void setEquationName(std::string s){equationName = s;};
        //get expression from equation, estarting with the next token after '=' 
        void setExpression(std::string s) {int eqPos = s.find('='); expression = s.substr(eqPos + 1, s.length() - (eqPos + 1));}

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
            case Error::Repeated:
                std::cout << "Repeated variable";
                break;
            case Error::NonDeclared:
                std::cout << "NonDeclared";
                break;
            }
            std::cout <<" Error In :"<< s <<std::endl;
            exit(1);
        }
};


