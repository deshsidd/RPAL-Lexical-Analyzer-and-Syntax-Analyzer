//
//  token.hpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/7/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#ifndef token_hpp
#define token_hpp


#include <iostream>
#include <string>
using namespace std;

class Token{
public:
    Token();
    Token(int t_type);
    Token(string t_value);
    Token(string t_value,int t_type);
    int type();
    string value();
    void setType(int t_type);
    void setValue(string t_value);
    
    enum Types { LETTER = 0,
        DIGIT = 1,
        OPERATOR = 2,
        STRING =  3,
        SPACE = 4,
        PUNCTION = 5,
        ENDOFFILE = 6,
        ERROR = 7,
        COMMENT = 8
    };
    
    string token_value;
    int token_type;
    
};
#endif /* token_hpp */
