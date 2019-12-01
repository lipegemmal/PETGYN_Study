#include <iostream>
#include <ostream>
#include <fstream>
#include <stdlib.h>

#include "equationManager.h"
//#include "texBison.tab.h"
#include "texLexer.h"
#include "texBison.tab.h"

EquationManager::EquationManager(std::string s){
    setEquation(s);

    sintatic = new SINTATIC(s);


   
    std::cout << "Parsing" << std::endl;
    yy_scan_string(eq.c_str());
    yyparse(&eq_resolved, sintatic);

    
    setName( sintatic->getName() );
    setExpressao(sintatic->getExpression());
    setVariableList( sintatic->getVariableList() ); 


    std::cout << "EqExpressao:" << getExpressao() << std::endl;
    std::cout << "Variable list" << std::endl;
        for(int i=0 ; i < countVariableList() ; i++ ){
            std::cout << getVariable(i) << " ";
        }
        std::cout << std::endl;

}

EquationManager::~EquationManager(){
    sintatic->~SINTATIC();
    free(sintatic);
}

void EquationManager::generatePdfFile(){
    std::string tex_file = getName();
    std::string compile = "pdflatex " + tex_file + " > /dev/null 2>&1";
    std::string convert = "convert -density 300 -depth 8 -quality 85 "+ tex_file+".pdf "+ tex_file+".png";
    system(compile.c_str());

    system(convert.c_str());
    //system("pdflatex teste.tex");
    return;
}

void EquationManager::generateLatexFile(){
    std::ofstream l_file;
    std::string full_name = getName()+".tex";
    //char *eq_resolved;


    //std::cout << "Parsing" <<std::endl;
    //yy_scan_string(eq.c_str());
    //yyparse(&eq_resolved);

    std::cout << "Opening File"<< std::endl;
    //cout << eq_resolved <<endl;
    //std::string trigfunctions ="\\DeclareMathOperator{\\asin}{asin}\n";
    //trigfunctions += "\\DeclareMathOperator{\\acos}{acos}\n";
    //trigfunctions+="\\DeclareMathOperator{\\atan}{atan}\n";
    //trigfunctions += "\\DeclareMathOperator{\\sinh}{sinh}\n";
    //trigfunctions += "\\DeclareMathOperator{\\cosh}{cosh}\n";
    //trigfunctions += "\\DeclareMathOperator{\\tanh}{tanh}\n";

    l_file.open(full_name.c_str());
    
    l_file << "\\documentclass[preview,border=1pt]{standalone}\n";
    l_file <<"\\usepackage{siunitx}\n";
    l_file <<"\\usepackage{amsmath}\n";
    //l_file << trigfunctions;
    l_file << "\\begin{document}\n";
    l_file << "$\n";
    l_file << eq_resolved;
    l_file <<"\n$\n";
    l_file << "\\end{document}\n";

    l_file.close();


    std::cout << "Arquivo tex gerado \n";

    yylex_destroy();
    generatePdfFile();
    
    std::cout << "Arquivo Pdf gerado\n";
    
    free(eq_resolved);
    return;
}


void EquationManager::generateDynamicLib (){
    std::ofstream c_file;
    std::string full_name = getName() + ".c";

    int variableQtd = countVariableList();

    std::cout << "Gerando arquivo c" << std::endl;

    c_file.open(full_name.c_str());

    c_file << "#include <math.h>\n#include <stdio.h>\n\n";
    c_file << "double " + getName() + "(";
    for (int i = 0; i < variableQtd; i++)
    {
        c_file << "double " + getVariable(i);
        //this prevents the extra ','
        if (i + 1 != variableQtd)
        {
            c_file << ",";
        }
    }
    c_file << "){\n\n";
    c_file << "return " + getExpressao() + " ; \n}\n";

    //criando a main

    c_file << "int main(){\n";
    //criando as variaveis para colocar os valores
    if (variableQtd != 0)
    {
        c_file << "double ";
        for (int i = 0; i < variableQtd; i++)
        {
            c_file << "a" + std::to_string(i);
            if (i != variableQtd - 1)
            {
                c_file << ",";
            }
        }
        c_file << ";\n";
        //lendo os valores usando scanf
        c_file << "scanf(\"";
        for (int i = 0; i < variableQtd; i++)
        {
            c_file << "%lf";
        }
        c_file << "\", ";

        for (int i = 0; i < variableQtd; i++)
        {
            c_file << "&a" + std::to_string(i);
            if (i != variableQtd - 1)
            {
                c_file << ",";
            }
        }
        c_file << ");\n";
        //chamando funções utilizando as variaveis

        c_file << "printf(\"%lf\\n\", " + getName() + "(";
        for (int i = 0; i < variableQtd; i++)
        {
            c_file << "a" + std::to_string(i);
            if (i != variableQtd - 1)
            {
                c_file << ",";
            }
        }
        c_file << "));\n return 0;\n}";
    }
    else
    {
        c_file << " printf(\"%lf\\n\", " + getName() + ");\n";
        c_file << "return 0;\n}";
    }
    
    c_file.close();
    
    std::cout << "Arquivo c gerado" << std::endl;

    std::cout << "compilando arquivo usando gcc" << std::endl;

    std::string gcc_call = "gcc -o "+getName() +" "+getName()+".c -lm";

    system(gcc_call.c_str());


}
