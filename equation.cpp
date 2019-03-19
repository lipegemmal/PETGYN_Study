#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "equation.h"

using namespace std;

Equation::Equation(string s){
    setEquation(s);
}

void Equation::setEquation(string s){
    eq = s;
    return;
}

string Equation::getEquation(){
    return eq;
}

void Equation::setResult(double d){
    result = d;
    return;
}

double Equation::getResult(){
    return result;
}

void Equation::generatePdfFile(string tex_file){
    string command = "pdflatex " + tex_file;

    system(command.c_str());
    return;
}

void Equation::generateLatexFile(string file_name){
    ofstream l_file;
    string full_name = file_name+".tex";

    l_file.open(full_name.c_str());
    
    l_file << "\\documentclass[preview]{standalone}\n\n";
    l_file << "\\begin{document}\n";
    l_file << "$\n";
    l_file << eq +"\n";
    l_file <<"$\n";
    l_file << "\\end{document}\n";

    l_file.close();

    generatePdfFile(file_name);
    return;

}
