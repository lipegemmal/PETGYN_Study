#include "sintaticAnalizer.h"
#include <iostream>
#include <memory>




int main(){

    std::unique_ptr<SINTATIC> s(new SINTATIC ("T1 (A,B,C) = 12+2/3*4") );

    s->cabecalho();
    s->expressao();
   // std::cout << s->getTop().getToken() <<std::endl;

    return 0;
}


void SINTATIC::cabecalho(){
    int cont = 0;

    std::string str = lex->getNextToken();

    if(lex->getType() != TokenTypes::Identifier)
        errorExit(Error::NonIdentifier,"cabecalho");
 
    else{
        //Colocar o nome da função na tabela de simbolos
        str = lex->getNextToken();
        if(str[0] == '(' )
        {
            while(str[0] != ')'){
                str = lex->getNextToken();
                //colocar o identificador do parametro na tabela de simbolos
        
                if(lex->getType() == TokenTypes::Identifier){
                    std::cout<<"found ID:"<< str <<std::endl;//aqui foi ignorado o limite máximo de variaveis
                }
                else{
                    //comparando com o anasint.c não faz sentido
                    if( str[0] != ',' && str[0] != ')' )
                        errorExit(Error::UnknownSimbol,"cabecalho");
                }
            }
        }
        str = lex->getNextToken();

        if(str[0] == '='){
            return;
        }
        else{
            //std::cout << str <<std::endl;
            errorExit(Error::NonAtribuition,"cabecalho");
        }
    }    
}

void SINTATIC::expressao(){
    emptyPile();
    char prec;
    
    TOKEN *t = new TOKEN("#",TokenTypes::Simbol);
    
    empileToken(*t);
    //simbant ignorado
    std::string str =lex->getNextToken();
    if(str[0] == ' ')
        errorExit(Error::Empty,"expressao");
    
    while(1){
        t = new TOKEN(str,lex->getType());
        prec = precedence(*t);
        if( prec == '<' || prec == '='){
            empileToken(*t);
            if(t->getType() != TokenTypes::FileEnd){
                str = lex->getNextToken();
                
                if (str[0] == ' ')
                    errorExit(Error::Empty, "expressao");
                
                else{
                    if(lex->getType() == TokenTypes::FileEnd){
                        str = "#";
                    }
                }

            }
        }
        else{
            if ( prec == '>'){
                do{
                    *t = getTop();
                    popPile();
                    prec = precedence(*t);
                    std::cout<<t->getToken()<<std::endl;
                    free(t);
                }while(prec != '<');
            }
            //geração de código
            else{
                errorExit(Error::Empty,"Geração de código");
            }
        }
        //comparação de pilha vazia testada por ultimo
        if(getTop().getToken() == "#" && str == "#")
            return;
    }
}

char SINTATIC::precedence(TOKEN t){

    int posTop=-1,posToken=-1;

    //getting stack top's position on precedence table
    switch(getTop().getType()){
        case TokenTypes::Identifier : posTop = (int)TokenTypes::Identifier; 
            break;
        case TokenTypes::Pre_def_func : posTop = (int)TokenTypes::Pre_def_func;
            break;
        case TokenTypes::Const : posTop = (int)TokenTypes::Const;
            break;
        case TokenTypes::Number : posTop = (int)TokenTypes::Number;
            break;
        case TokenTypes::Simbol : posTop = getPrecPos(getTop().getToken()[0]);   
    }

    switch(t.getType()){
        case TokenTypes::Identifier : posToken = (int)TokenTypes::Identifier;
            break;
        case TokenTypes::Pre_def_func : posToken = (int)TokenTypes::Pre_def_func;
            break;
        case TokenTypes::Const : posToken = (int)TokenTypes::Const;
            break;
        case TokenTypes::Number : posToken = (int)TokenTypes::Number;
            break;
        case TokenTypes::Simbol : posToken = getPrecPos(t.getToken()[0]);
            break;
        case TokenTypes::FileEnd : posToken = getPrecPos(t.getToken()[0]); //check, this one could result in bugs
    }
    return getPrecedence(posTop+1,posToken);
}

SINTATIC::SINTATIC(std::string s){
    emptyPile();
    lex = new LEXER(s);
    
}

SINTATIC::~SINTATIC(){
    free(lex);
}
