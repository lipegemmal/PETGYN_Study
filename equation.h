#include <string>

using namespace std;

class Equation{
    private:
      std::string eq;
     // char *eq_resolved;
      double result;
      void setEquation(string s);
  

    public:
        Equation(string s);
        string getEquation();
        double getResult();
        void generatePdfFile(string tex_file);
        void generateLatexFile(string file_name);
        void resolveEquation();
};


//