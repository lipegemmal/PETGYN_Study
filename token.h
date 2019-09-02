#include "libTypes.h"

class TOKEN{
    private:

    TokenTypes type;
    std::string token;


    public:

    TokenTypes getType(){return type;};
    std::string getToken(){return token; };
    TOKEN( std::string tok, TokenTypes typ){type = typ; token = tok;};
    void SetToken(std::string tok, TokenTypes typ){type = typ; token = tok;};

    
};
