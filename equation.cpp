#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "equation.h"
//#include "solveBison.tab.h"
//#include "solveLexer.h"
#include "texBison.tab.h"
#include "texLexer.h"

using namespace std;

Equation::Equation(string s){
    setEquation(s);
}

void Equation::setEquation(string s){
    eq = s +"\n";
    return;
}

string Equation::getEquation(){
    return eq;
}

double Equation::getResult(){
    return result;
}

void Equation::generatePdfFile(string tex_file){
    string command = "pdflatex " + tex_file + " > /dev/null 2>&1";

    system(command.c_str());
    //system("pdflatex teste.tex");
    return;
}

void Equation::generateLatexFile(string file_name){
    ofstream l_file;
    string full_name = file_name+".tex";
    char *eq_resolved;

    yy_scan_string(eq.c_str());

    yyparse(&eq_resolved);

    //cout << eq_resolved <<endl;


    
    l_file.open(full_name.c_str());
    
    l_file << "\\documentclass[preview,border=1pt]{standalone}\n\n";
    l_file << "\\begin{document}\n";
    l_file << "$\n";
    l_file << eq_resolved;
    l_file <<"\n$\n";
    l_file << "\\end{document}\n";

    l_file.close();

    cout << "Arquivo tex gerado \n";

    generatePdfFile(file_name);
    
    cout << "Arquivo Pdf gerado\n";
    
    return;

}

void Equation::resolveEquation(){

    //include test to verify if it can be solved

   // yy_scan_string(eq.c_str());

   // yyparse(&result);

    return;
}
