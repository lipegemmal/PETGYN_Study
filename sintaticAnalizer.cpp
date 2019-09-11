#include "sintaticAnalizer.h"
#include <iostream>


SINTATIC::SINTATIC(std::string s){
    setExpression(s);
}

SINTATIC::~SINTATIC(){
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

