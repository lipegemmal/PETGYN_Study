#include <iostream>
#include <string>

#include "equationManager.h"


int main(){
    EquationManager *teste = new EquationManager("F2 (a , b , x ) =  ( sin(a) + TAN(b)) * COS (x)");

   teste->generateLatexFile();

    teste->generateDynamicLib();






    delete teste;
    return 0;
}