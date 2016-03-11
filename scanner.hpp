//
//  scanner.hpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/6/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#ifndef scanner_hpp
#define scanner_hpp


#include <iostream>
#include <string>
#include "token.hpp"
using namespace std;

string scan();

//enum {DIGIT, LETTER, IDENT, INT_LIT, ERROR, SPACE, STOP, PLUS_CODE};

class LexicalAnalysis
{
    
public:
    Token token;
    int cClass;
    string str;
    
private:
    char next;
    
public:
    Token scan();
    LexicalAnalysis(string str);
    
    Token peek();
    int pClass;
    void paddChar();
    void pgetChar();
    char pnext;
    int pctr;
    Token next_token;
    
    
private:
    void addChar();
    void getChar();
    bool isSpace(char next);
    bool isOperator(char next);
    bool isPunction(char next);
    bool isDigit(char next);
    bool isLetter(char next);
    bool isCommentChar(char next);
    bool isStringChar(char next);
    
};


#endif /* scanner_hpp */
