//Ainda é legal modifical os erros

#include "lexicalAnalizer.h"



LEXER::LEXER(std::string s){
    setSymbols(s);
    includeEndChar();
    setSymbPos(0);
    setState(States::A0);
    setType(TokenTypes::None);
    setLastSymbol(' ');
    
}

std::string LEXER::getNextToken(){
    //if all tokens have already been processed
    if( isFinished() == true){ 
        setType(TokenTypes::FileEnd);
        return "\0";
    }
    
    token.clear();

    setType(TokenTypes::None);
    setState(States::A0);

    while(getState() != States::A8){
        switch (state){

            case States::A0: A0();
                break;
            case States::A1: A1();
                break;
            case States::A2: A2();
                break;
            case States::A3: A3();
                break;        
            case States::A4: A4();
                break;
            case States::A5: A5();
                break;
            case States::A6: A6();
                break;
            case States::A7: A7();
                break;
            default:    //should return an error message
                break;
        }
    }
    //precisa colocar pois não tem incremento no inicio do original
    //se não o algoritmo vai comer um caracter e/ou acessar caracteres lixo
    incSymbPos(-2);
    setLastSymbol(getCurChar());
    incSymbPos();
    //std::cout<<"Token "<<getToken()<<" CurChar:"<<getCurChar()<<std::endl;
    return getToken();
}


//State functions

void LEXER::A0(){
    char c = getCurChar();

   if(c == '\0'){
       setType(TokenTypes::FileEnd);
       setState(States::A8);
   }

   if(isblank(c)){
   }
   else if(isdigit(c)){
        S1(c);
        setState(States::A1);
    }
        else if(c == '.'){
            S1(c);
            setState(States::A2);
        }
            else if(c == '+' || c == '-'){
                S5(c);
                setState(States::A8);
            }
                else if(isalpha(c)){
                    S6(c);
                    setState(States::A6);
                }
                    else if(isValid(c)){
                        S6(c);
                        setState(States::A7);
                    }
                    else
                        errorExit(Error::UnknownSimbol);    
    incSymbPos();
    return;
}   

void LEXER::A1(){
    char c = getCurChar();

    if(isdigit(c)){
        S2(c);
    }
        else if( c == '.'){
            S2(c);
            setState(States::A4);
        }
            else if(c == 'E' || c == 'e'){
                S2(c);
                setState(States::A3);
            }
                else if(isValid(c)){
                    S3(c);
                    setState(States::A8);
                }
                    else
                        errorExit(Error::UnknownSimbol);

    incSymbPos();
    return;
}

void LEXER::A2(){
    char c = getCurChar();

    if(isdigit(c)){
        S2(c);
        setState(States::A4);
    }
        else if(isValid(c)){
            S4(c);
            setState(States::A8);
        }
            else
                errorExit(Error::UnknownSimbol);

    incSymbPos();
    return;
}

void LEXER::A3(){
    char c = getCurChar();

    if(isdigit(c) || c == '+' || c == '-'){
        S2(c);
        setState(States::A5);
    }
        else
            errorExit(Error::UnknownSimbol);
    
    incSymbPos();
    return;
}

void LEXER::A4(){
    char c = getCurChar();
    
    if(isdigit(c)){
        S2(c);
    }
        else if(c == 'E' || c == 'e'){
            S2(c);
            setState(States::A3);
        }
            else if(isValid(c)){
                S3(c);
                setState(States::A8);
            }
                else
                    errorExit(Error::UnknownSimbol);

    incSymbPos();
    return;
}

void LEXER::A5(){
    char c = getCurChar();

    if(isdigit(c)){
        S2(c);
    }
        else if(isValid(c)){
            S3(c);
            setState(States::A8);
        }
            else
                errorExit(Error::UnknownSimbol);
                
    incSymbPos();
    return;
}

void LEXER::A6(){
    char c = getCurChar();

    if(isalnum(c)){
        S7(c);
    }
        else if(isSpecial(c) || isspace(c)){
            S8(c);
            setState(States::A8);
        }
            else
                errorExit(Error::UnknownSimbol);

    incSymbPos();
    return;
}

void LEXER::A7(){
    char c = getCurChar();

    if(isValid(c)){
        S9(c);
        setState(States::A8);
    }
        else{
            errorExit(Error::UnknownSimbol);
        }
    incSymbPos();
    return;
}

//State Processing functions

void LEXER::S1(char c){
    setType(TokenTypes::Number);
    setLastSymbol(0);
    concatToken(c);
}

void LEXER::S2(char c){
    concatToken(c);
}

void LEXER::S3(char c){
    setValue();
    if(getValue() == 0)
        errorExit(Error::Overflow);
}

void LEXER::S4(char c){
    setType(TokenTypes::Simbol);    
    //aqui não ocorre concatenação
}

void LEXER::S5(char c){
    setType(TokenTypes::Simbol);

    if(isPreUnary(getLastSymbol())){
        if(c == '-')
            concatToken('!');
        else
            concatToken('?');
    }
    else
        concatToken(c);

    setLastSymbol(c);
    incSymbPos();
}

void LEXER::S6(char c){
    concatToken(c);

    if(isPreUnary(c))
        setLastSymbol(c);
    else
        setLastSymbol(0);
}

void LEXER::S7(char c){
    concatToken(c);
}

void LEXER::S8(char c){
    if(
        isReserved(getToken())
        ){
        //setType(TokenTypes::Reserved);
        setType(TokenTypes::Pre_def_func);
    }
    else
        setType(TokenTypes::Identifier);
}

void LEXER::S9(char c){
    setType(TokenTypes::Simbol);
}


//Auxiliar Functions

bool LEXER::isReserved(std::string token){
    std::vector<std::string> reserved = getReservedWords();
    
    for(int i = 0 ; i < reserved.size(); i++ ){
        if(reserved[i].compare(token) == 0){
            return true;
        }
    }
    return false;
}