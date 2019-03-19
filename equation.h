#include <string>

using namespace std;

class Equation{
    private:
      std::string eq;
      double result;
      void setEquation(string s);
      
    public:
        Equation(string s);
        string getEquation();
        void setResult(double d);
        double getResult();
        void generatePdfFile(string tex_file);
        void generateLatexFile(string file_name);
        
};