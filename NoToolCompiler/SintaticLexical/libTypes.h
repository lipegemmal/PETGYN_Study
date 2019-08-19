#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <stack>

#ifndef LIBTYPES
#define LIBTYPES

//enum class for errors
enum class Error {UnknownSimbol,Overflow,NonIdentifier,NonAtribuition,Empty};

const std::string specialCharacters = {".,=()^*/+- "};
const std::string preUnaryCharacters = {",(^*/+- "};

const std::vector<std::string> reservedWords = {"ABS",
                                          "ACOS",
                                          "ASIN",
                                          "ATAN",
                                          "COS",
                                          "COSH",
                                          "EXP",
                                          "LN",
                                          "LOG",
                                          "NEP",
                                          "PI",
                                          "SIN",
                                          "SINH",
                                          "SQRT",
                                          "TAN",
                                          "TANH"};

// enum class Classes , >10 value numbers based on precedences table!
enum class TokenTypes : int
{
    None = 0,
    Simbol = 3,
    Reserved = 4,
    FileEnd = 5,
    Pre_def_func = 11,
    Identifier = 12,
    Const = 13,
    Number = 14
};

const std::vector<std::string> precedences = {"#+-*/^!?(),    ",
                                        " <<<<<<<<  <<<<",  /* #             */
                                        ">>><<<<<<> <<<<",  /* +             */
                                        ">>><<<<<<> <<<<",  /* -             */
                                        ">>>>><<<<> <<<<",  /* *             */
                                        ">>>>><<<<> <<<<",  /* /             */
                                        ">>>>><<<<> <<<<",  /* ^             */
                                        ">>>>>>  <> <<<<",  /* !             */
                                        ">>>>>>  <> <<<<",  /* ?             */
                                        " <<<<<<<<==<<<<",  /* (             */
                                        ">>>>>>>> >>    ",  /* )             */
                                        "      <<<==<<<<",  /* ,             */
                                        ">>>>>>>><>     ",  /* funcao        */
                                        ">>>>>>>>=>>    ",  /* identificador */
                                        ">>>>>>>> >>    ",  /* constante     */
                                        ">>>>>>>> >>    "}; /* numero     */

#endif
