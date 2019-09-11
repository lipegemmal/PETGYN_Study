#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "equationManager.h"
#include "texBison.tab.h"
#include "texLexer.h"

EquationManager::EquationManager(std::string s){
    setEquation(s);

    sintatic = std::unique_ptr<SINTATIC>(new SINTATIC(s));

    sintatic->cabecalho();
    sintatic->expressao();

    setName( sintatic->getName() );
    setExpressao( sintatic->getExpression() );
    setVariableList( sintatic->getVariableList() ); 

    std::cout << "EqName:" << getName() <<std::endl;
    std::cout << "EqExpressao:" << getExpressao() << std::endl;
    std::cout << "Variable list" << std::endl;
        for(int i=0 ; i < countVariableList() ; i++ ){
            std::cout << getVariable(i) << " ";
        }
        std::cout << std::endl;

}

EquationManager::~EquationManager(){
    sintatic.reset();
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
    char *eq_resolved;


    std::cout << "Parsing" <<std::endl;
    yy_scan_string(eq.c_str());
    yyparse(&eq_resolved);

    std::cout << "Opening File"<< std::endl;
    //cout << eq_resolved <<endl;
    std::string trigfunctions ="\\DeclareMathOperator{\\asin}{asin}\n";
    trigfunctions += "\\DeclareMathOperator{\\acos}{acos}\n";
    trigfunctions+="\\DeclareMathOperator{\\atan}{atan}\n";
    //trigfunctions += "\\DeclareMathOperator{\\sinh}{sinh}\n";
    //trigfunctions += "\\DeclareMathOperator{\\cosh}{cosh}\n";
    //trigfunctions += "\\DeclareMathOperator{\\tanh}{tanh}\n";

    l_file.open(full_name.c_str());
    
    l_file << "\\documentclass[preview,border=1pt]{standalone}\n";
    l_file <<"\\usepackage{siunitx}\n";
    l_file <<"\\usepackage{amsmath}\n";
    l_file << trigfunctions;
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

    std::cout << "Gerando arquivo c" <<std::endl;

    c_file.open(full_name.c_str());

    c_file << "#include <math.h>\n\n";
    c_file << "double "+ getName() + "(";
        for(int i = 0; i < variableQtd ; i++){
            c_file << "double " + getVariable(i);
            //this prevents the extra ','
            if( i+1 != variableQtd){
                c_file << ",";
            } 
        }    
    c_file << "){\n\n";
    c_file << "return "+ getExpressao() +" ; \n}";

    c_file.close();

    std::cout << "Arquivo c gerado" << std::endl;

}
