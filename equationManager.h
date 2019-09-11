#include <string>
#include <vector>
#include <memory>

#include "sintaticAnalizer.h"


class EquationManager{
    private:
      
      SINTATIC *sintatic;

      std::string eqName;
      std::string eqExpressao;
      std::string eq;
      std::vector< std::string> variableList;
      char *eq_resolved;

      void setEquation(std::string s){eq = s +"\n";};
      void setName(std::string s){eqName = s;};
      void setExpressao(std::string s){eqExpressao = s;};
      void setVariableList(std::vector<std::string> s) { variableList = s; };

    public:
        EquationManager(std::string s);
        ~EquationManager();
        std::string getEquation() { return eq; };
        std::string getName(){return eqName;};
        std::string getExpressao(){return eqExpressao;};
        int countVariableList(){return variableList.size(); };
        std::string getVariable(int pos){return variableList[pos]; };

        void generatePdfFile();
        void generateLatexFile();
        void generateDynamicLib();
};

