#include <iostream>

#include "equation.h"


int main(){
    Equation *teste = new Equation("(ax+b)/2" );
    string name = "test";

    
    teste->generateLatexFile(name);


   // teste->resolveEquation();

    //cout << teste->getResult() <<endl;


    return 0;
}