#include <string>
#include <cctype>


class LEXER{

    
    public:        
        // enum class Classes 
        enum class TokenTypes {None,Number,Simbol};

        //enum class For DFA states
        enum class States { A0,A1,A2,A3,A4,A5,A6,A7,A8 };
        
        //Constructor
        LEXER(std::string simbols);
        
        //Analyses simbols string and returns the next token
        std::string getNextToken();
        
        //Checks if all of the simbols string has been analysed
        bool isFinished(){ return symbolPosition == symbols.size() ?  true :  false;};

        
        /*Gets*/
        States getState(){return state;};
        TokenTypes getType(){return tokentype;};
        char getCurChar() { return symbols[symbolPosition]; };
        std::string getSpecialChars(){return specialCharacters;};
        std::string getPreUnaryChars(){return preUnaryCharacters;};
        std::string getSymbols(){return symbols;};
    private:    
        States state;
        TokenTypes tokentype; 
        std::string symbols;
        uint symbolPosition;
        std::string token;
        char lastSymbol;

        std::string specialCharacters = {".,=()^*/+-"};
        std::string preUnaryCharacters = {",(^*/+-"};

        bool isSpecial(char c) { return specialCharacters.find(c) != -1 ? true : false; };
        bool isPreUnary(char c) { return preUnaryCharacters.find(c) != -1 ? true : false; };

        /*State Functions*/
        void A0(); //Start
        //void A1();
        //void A2();
        //void A3();    //For exponentials ('e','E')
        //void A4();
        //void A5();
        //void A6();
        //void A7();

        /*State Ṕrocessing auxiliars*/
        void S1(char c);
        //void S2(char c);
        //void S3(char c);
        //void S4(char c);
        void S5(char c);
        void S6(char c);
        //void S7(char c);
        //void S8(char c);
        //void S9(char c);

        /*Private sets*/
        void setSymbPos(int n){symbolPosition=n;};
        void incSymbPos(){ symbolPosition++;};
        void concatToken(char c){ token += c;};
        void setState(States s) { state = s;};
        void setType(TokenTypes t){ tokentype = t;}
        void setLastSymbol(char c){lastSymbol = c;};
        void setSymbols(std::string s){symbols=s;};

        /*Auxiliar Functions*/
};  