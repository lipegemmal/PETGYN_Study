#include "sintaticAnalizer.h"
#include <iostream>




/*
int main(){

    //std::string a;
    //std::cout << "Digite a equacao:" <<std::endl;
    //getline(std::cin, a);
    //std::unique_ptr<SINTATIC> s(new SINTATIC(a));

    std::unique_ptr<SINTATIC> s(new SINTATIC (" F1 (a,b,x) = a*b + a*x") );
    
    s->cabecalho();
    s->expressao();
   // std::cout << s->getTop().getToken() <<std::endl;

    std::cout <<"EquationName:" << s->getName() << std::endl;
    std::cout <<"Expression:" << s->getExpression() << std::endl;

   
    return 0;
}
*/

void SINTATIC::cabecalho(){
    int cont = 0;

    std::string str = lex->getNextToken();

    if(lex->getType() != TokenTypes::Identifier)
        errorExit(Error::NonIdentifier,"cabecalho");
 
    else{
        setEquationName(str);
        //Colocar o nome da função na tabela de simbolos
        str = lex->getNextToken();
        if(str[0] == '(' )
        {
            while(str[0] != ')'){
                str = lex->getNextToken();
                //colocar o identificador do parametro na tabela de simbolos
        
                if(lex->getType() == TokenTypes::Identifier){
                    //std::cout<<"found ID:"<< str <<std::endl;//aqui foi ignorado o limite máximo de variaveis
                    if(isInList(str) == false){
                        insertVariableList(str);
                    }
                    std::cout << "ID inserted:" << getVariableName(cont) << std::endl;
                    cont++;
                }
                else{
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
        
        //verifica se usa um identificador não declarado
        if (t->getType() == TokenTypes::Identifier){
            std::cout << "Testing Token:" << t->getToken() <<std::endl;
            if(isInList(t->getToken()) == false){
                    std::cout <<"Simbolo não declarado!!" << std::endl;
                    //*** Retornar erro de uso de identificador não declarado
            }
            //std::cout <<"Token passed!" <<std::endl;
        }

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
    
    setExpression(s);
    lex = new LEXER(s);
}

SINTATIC::~SINTATIC(){
    free(lex);
}

//Test if s is in the list, used to check repetitions or undeclared variables use.
bool SINTATIC::isInList(std::string s){
    for(int i = 0 ; i < countVariableList() ; i++){
        if( s == getVariableName(i))
            return true;
    }

    // if the list is empty or s doesn't match any element in list
    return false;
}