#include <iostream>

#include "equationManager.h"


int main(){
    EquationManager *teste = new EquationManager("F1(a,b,x) =  (a*b) + a*x");

   //teste->generateLatexFile();

    teste->generateDynamicLib();


    delete teste;
    return 0;
}