//
//  token.cpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/7/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#include "token.hpp"

Token::Token()
{
    token_value=" ";
    token_type=ERROR;
}

Token::Token(int t_type)
{
    token_value=" ";
    token_type=t_type;
}

Token::Token(string t_value)
{
    token_value=t_value;
    token_type=ERROR;
}

Token::Token(string t_value, int t_type)
{
    token_value=t_value;
    token_type=t_type;
}

int Token::type()
{
    return token_type;
}

string Token::value()
{
    return token_value;
}

void Token::setType(int t_type)
{
    token_type=t_type;
}

void Token::setValue(string t_value)
{
    token_value=t_value;
}
