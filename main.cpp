#include <iostream>
#include <string>

#include "equationManager.h"

int main(int argc,char const *argv[]){
    
    //if (argc != 2){
      //  std::cout << "Numero de argumentos errado!" <<std::endl;
        //exit(1);
   // }


    std::cout<<argv[0] <<std::endl;
    std::cout << argv[1] <<std::endl;


    //EquationManager *teste = new EquationManager(argv[1]);

    EquationManager *teste = new EquationManager("t1(ca,va,xa,fa) = ((3.6 * ca)/va) *(1 + (xa/(2500*fa)) + pow((xa/(500*fa)),3)) ");
    //((3.6 * ca)/va) * ( 1 + (xa/(2500*fa)) + (xa/(500*fa))^3)

    teste->generateLatexFile();
   
    teste->generatePdfFile();

    teste->generateDynamicLib();






    //delete teste;
    return 0;
}
