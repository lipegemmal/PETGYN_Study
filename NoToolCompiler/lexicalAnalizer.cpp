#include "lexicalAnalizer.h"



LEXER::LEXER(std::string s){
    setSymbols(s);
    setSymbPos(0);
    setState(States::A0);
    setType(TokenTypes::None);
    
}

std::string LEXER::getNextToken(){
    //if all tokens have already been processed
    if( isFinished() ){ return " ";}
    
    
    token.clear();

    tokentype = TokenTypes::None;
    state = States::A0;

    while(state != States::A8){
        switch (state){

            case States::A0: A0();

            case States::A1:

            case States::A2:

            case States::A3:
        
            case States::A4:

            case States::A5:

            case States::A6:

            case States::A7:
                break;
            
            default:    //should return an error message
                break;
        }
    }

}




//State functions

void LEXER::A0(){
    char c = getCurChar();

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
       
   

    incSymbPos();
    return;
}   









//State Processing functions

void LEXER::S1(char c){
    setType(TokenTypes::Number);
    concatToken(c);
}

void LEXER::S5(char c){
    setType(TokenTypes::Simbol);

    if(isPreUnary(c)){
        if(c == '-')
            concatToken('!');
        else
            concatToken('?');
    }
    else
        concatToken(c);
        
    setLastSymbol(c);
}

//Auxiliar Functions
