#include <utility>
#include <vector>
#include <string>

class SINTATIC{

    public:
        std::string getName(){return equationName;};
        void setEquationName(std::string s) { equationName = s; };
        

        
        std::string getExpression(){return expression;};
        
        SINTATIC(std::string s);
        ~SINTATIC();

        void insertVariableList(std::string s) { variableList.push_back(s); };
        bool isVariableListEmpty(){return variableList.empty();};
        int countVariableList(){return variableList.size();};
        bool isInList(std::string s);
        std::string getVariableName(int pos){return variableList[pos];};
        std::vector<std::string> getVariableList(){return variableList;};

    private:
        std::string expression;
        std::string equationName;
        std::vector< std::string > variableList;
       
        void emptyVariableList(){variableList.clear();}
        
        //compares TOKEN t precedence with pile.top()'s token
        //char precedence(TOKEN t);
       
        //get expression from equation, estarting with the next token after '=' 
        void setExpression(std::string s) {int eqPos = s.find('='); expression = s.substr(eqPos + 1, s.length() - (eqPos + 1));}

        
};


