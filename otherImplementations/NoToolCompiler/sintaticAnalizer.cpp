#include "sintaticAnalizer.h"


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

