#include <string>
#include <cctype>
#include <vector>
#include <iostream>

class LEXER{

    
    public:        
        // enum class Classes 
        enum class TokenTypes {None=0,Number=1,Identifier=2,Simbol=3,Reserved=4,FileEnd=5, Const=6 , Pre_def_func=7};

        //enum class For DFA states
        enum class States { A0,A1,A2,A3,A4,A5,A6,A7,A8 };
        
        //enum class for errors
        enum class Error {UnknownSimbol,Overflow};

        //Constructor
        LEXER(std::string simbols);
                //Analyses simbols string and returns the next token
        std::string getNextToken();
        
        //Checks if all of the simbols string has been analysed
        bool isFinished(){ return symbolPosition == symbols.size()-1? true :  false;};

        
        /*Gets*/
        States getState(){return state;};
        TokenTypes getType(){return tokentype;};
        char getCurChar() { return symbols[symbolPosition]; };
        std::string getSpecialChars(){return specialCharacters;};
        std::string getPreUnaryChars(){return preUnaryCharacters;};
        std::string getSymbols(){return symbols;};
        char getLastSymbol(){return lastSymbol;};
        std::string getToken(){return token;}
        double getValue(){return value;};
        std::vector<std::string> getReservedWords(){return reservedWords;};
    private:    
        States state;
        TokenTypes tokentype; 
        std::string symbols;
        uint symbolPosition;
        std::string token;
        char lastSymbol;
        
        //value if number is converted, devo colocar uma flag?
        double value;

        std::string specialCharacters = {".,=()^*/+- "};
        std::string preUnaryCharacters = {",(^*/+- "};
        
        std::vector<std::string> reservedWords ={"ABS",
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
                                        
        
        
        
        bool isSpecial(char c) { return specialCharacters.find(c) != -1 ? true : false; };
        bool isPreUnary(char c) { return preUnaryCharacters.find(c) != -1 ? true : false; };
        bool isValid(char c) {return (isalnum(c) || isSpecial(c) || isspace(c)) ? true : false; };
        bool isReserved(std::string token);
        /*State Functions*/
        //Start
        void A0(); 
        void A1();
        void A2();
        //For exponentials ('e','E')
        void A3();    
        void A4();
        void A5();
        void A6();
        void A7();

        /*State Ṕrocessing auxiliars*/
        void S1(char c);
        void S2(char c);
        void S3(char c);
        void S4(char c);
        void S5(char c);
        void S6(char c);
        void S7(char c);
        void S8(char c);
        void S9(char c);

        /*Private sets*/
        void setSymbPos(int n){symbolPosition=n;};
        void incSymbPos(int i=1){ symbolPosition+=i;};
        void includeEndChar(){symbols+=' ';};
        void concatToken(char c){ token += c;};
        void setState(States s) { state = s;};
        void setType(TokenTypes t){ tokentype = t;}
        void setLastSymbol(char c){lastSymbol = c;};
        void setSymbols(std::string s){symbols=s;};
        void setValue(){value = stof(token);};
        
        /*Auxiliar Functions*/

        //return State in String form 
        std::string showState(){
            States a = getState();
            switch(a){
                case States::A0:
                    return "A0";
                    break;
                case States::A1:
                    return "A1";
                    break;
                case States::A2:
                    return "A2";
                    break;
                case States::A3:
                    return "A3";
                    break;
                case States::A4:
                    return "A4";
                    break;
                case States::A5:
                    return "A5";
                    break;
                case States::A6:
                    return "A6";
                    break;
                case States::A7:
                    return "A7";
                    break;
                case States::A8:
                    return "A8";
                    break;
            }
        }

        //return Type in string format
        std::string showType(){
                TokenTypes a = getType();
                
                switch(a){
                    case TokenTypes::None:
                        return "None";
                    case TokenTypes::Number:
                        return "Number";
                    case TokenTypes::Identifier:
                        return "Identifier";
                    case TokenTypes::Simbol:
                        return "Simbol";
                    case TokenTypes::Reserved:
                        return "Reserved";
                    case TokenTypes::FileEnd:
                        return "FileEnd";
                }
        }

        //Error function
        void errorExit(Error e){
            switch (e){
                case Error::Overflow:
                    std::cout<<"Overflow";
                   break;
                case Error::UnknownSimbol:
                    std::cout<<"UnknownSimbol";
                    break;
            }
            std::cout<< " error in State: "<<showState() <<" with class: "<< showType()<<std::endl; 
            exit(1);
        }
};