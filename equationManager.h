#include <string>
#include <memory>

#include "sintaticAnalizer.h"


class EquationManager{
    private:
      
      std::unique_ptr<SINTATIC> sintatic;

      std::string eqName;
      std::string eqExpressao;
      std::string eq;
     
      void setEquation(std::string s){eq = s +"\n";};
      void setName(std::string s){eqName = s;};
      void setExpressao(std::string s){eqExpressao = s;};

    public:
        EquationManager(std::string s);
        ~EquationManager();
        std::string getEquation() { return eq; };
        void generatePdfFile();
        void generateLatexFile();
        std::string getName(){return eqName;};
        std::string getExpressao(){return eqExpressao;};
};

