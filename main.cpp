#include <iostream>

#include "equation.h"


int main(){
    //Equation *teste = new Equation("3.6*ca/va *[1+ xa/(2500*fa) +(xa/(500*fa))^3] + s*(3+3.6*ca/va)" );
    Equation *teste = new Equation("0 = x2");
    //Equation *teste = new Equation("t1(x,y) = sqrt(x^3) + y");
    string name = "test";

    
    teste->generateLatexFile(name);


   // teste->resolveEquation();

    //cout << teste->getResult() <<endl;

    delete teste;
    return 0;
}