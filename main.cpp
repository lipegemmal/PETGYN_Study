#include <iostream>

#include "equation.h"


int main(){
    //Equation *teste = new Equation("3.6*ca/va *[1+ xa/(2500*fa) +(xa/(500*fa))^3] + s*(3+3.6*ca/va)" );
    Equation *teste = new Equation("t2 = 2 * sinh(tanh((PI)^e)) * cosh(abs(21.2^ln(2)))");
    string name = "test";

    
    teste->generateLatexFile(name);


   // teste->resolveEquation();

    //cout << teste->getResult() <<endl;


    return 0;
}