//
//  scanner.cpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/6/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#include "scanner.hpp"
#include "token.hpp"
#include <string.h>
//string str="hello";


string reserved_words[] = {"let" ,"ls","le", "eq", "ne", "true", "false", "nil", "dummy","where", "in", "fn", "and", "rec", "within", "aug", "not", "or", "gr", "ge" };

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

LexicalAnalysis::LexicalAnalysis(string s): cClass(ERROR),str(s),next(' '),pClass(ERROR),pctr(0)
{
    Token token("",ERROR);
    getChar();
}

Token LexicalAnalysis::scan()
{
    if(cClass==ENDOFFILE)
    {
        token.token_type=ENDOFFILE;
        token.token_value="\0";
        return token;
    }
    
    token.setValue("");
    while(cClass == COMMENT | cClass==SPACE)
    {
        while(cClass==SPACE)
        {
            getChar();
        }
        if(cClass==COMMENT)
        {
            getChar();
            while(next!='\n')
            {
                getChar();
            }
            getChar();
        }
        
    }
    
    if(cClass==ENDOFFILE)
    {
        token.token_type=ENDOFFILE;
        token.token_value="\0";
        return token;
    }
    
    switch(cClass)
    {
        case LETTER:
            token.token_type = LETTER;
            addChar();
            getChar();
            while(cClass== DIGIT || cClass==LETTER || next=='_')
            {
                //cout<<"current letter char is :"<<next<<"with class :"<<cClass;
                addChar();
                getChar();
            }
            return token;
            break;
            
            
        case DIGIT:
            token.token_type = DIGIT;
            addChar();
            getChar();
            while(cClass==DIGIT)
            {
                addChar();
                getChar();
            }
            return token;
            break;
            
        case OPERATOR:
            token.token_type = OPERATOR;
            addChar();
            getChar();
            while(cClass==OPERATOR)
            {
                addChar();
                getChar();
            }
            return token;
            break;
            
        case PUNCTION:
            token.token_type = PUNCTION;
            addChar();
            getChar();
            return token;
            break;
            
        case STRING:
            token.token_type = STRING;
            addChar();
            getChar();
            while(isStringChar(next))
            {
                addChar();
                getChar();
            }
            if(next=='\'')
            {
                addChar();
                getChar();
                return token;
                break;
            }
            
        case COMMENT://cout<<"error. comments not properly removed";
            break;
            
        case SPACE://cout<< "error. space not properly removed";
            break;
            
        case ERROR://cout<<"an error occured of type ERROR";eak;
            break;
            
            
    }
    
    
    
    
    return token;
}


void LexicalAnalysis::getChar()
{
    if(str.size()>0)
    {
        
        next=str.at(0);
        str.erase(0,1);
        //cout<<"next char is :"<<next<<" \n";
    }
    else
    {
        cClass = ENDOFFILE;
        return;
    }
    
    if (isLetter(next))
    {
        
        //token.token_type = LETTER;
        cClass = LETTER;
        return;
    }
    else if(isDigit(next))
    {
        //token.token_type = DIGIT;
        cClass = DIGIT;
        return;
    }
    else if(next=='\'')
    {
        //token.token_type = STRING;
        cClass = STRING;
        return;
    }
    else if(isSpace(next))
    {
        //token.token_type = SPACE;
        cClass = SPACE;
        return;
    }
    
    else if(isPunction(next))
    {
        //token.token_type = PUNCTION;
        cClass = PUNCTION;
        return;
    }
    else if(next=='/' & str.size()>0 & str.at(0)=='/')
    {
        
        
            //token.token_type = COMMENT;
            cClass = COMMENT;
            return;
        
        
    }
    else if(isOperator(next))
    {
        //token.token_type = OPERATOR;
        cClass = OPERATOR;
        return;
    }
    else
    {
        //cout<<"error. next char did not match any type";
    }
   
    
}

void LexicalAnalysis::addChar()
{
    if(strcmp(&next,"\n")==0)
    {
        token.token_value=token.token_value + "\\n";
    }
    else if(strcmp(&next,"\n")==0)
    {
        token.token_value=token.token_value + "\\n";
    }
    else
    {
        token.token_value=token.token_value + next;
    }
    
    //cout<<"token value is :"<<token.token_value<<"\n";
}



Token LexicalAnalysis::peek()
{
    pClass=cClass;
    pnext=next;
    pctr=0;
    if(pClass==ENDOFFILE)
    {
        next_token.token_type=ENDOFFILE;
        next_token.token_value="\0";
        return next_token;
    }
    
    next_token.setValue("");
    do
    {
        while(pClass==SPACE)
        {
            pgetChar();
        }
        if(pClass==COMMENT)
        {
            pgetChar();
            while(isCommentChar(pnext) && pnext!='\n')
            {
                pgetChar();
            }
            pgetChar();
        }
        
    }while(pClass == COMMENT | pClass==SPACE);
    if(pClass==ENDOFFILE)
    {
        next_token.token_type=ENDOFFILE;
        next_token.token_value="\0";
        return next_token;
    }
    
    switch(pClass)
    {
        case LETTER:
            next_token.token_type = LETTER;
            paddChar();
            pgetChar();
            while(pClass== DIGIT || pClass==LETTER || pnext=='_')
            {
                paddChar();
                pgetChar();
            }
            return next_token;
            break;
            
            
        case DIGIT:
            next_token.token_type = DIGIT;
            paddChar();
            pgetChar();
            while(pClass==DIGIT)
            {
                paddChar();
                pgetChar();
            }
            return next_token;
            break;
            
        case OPERATOR:
            next_token.token_type = OPERATOR;
            paddChar();
            pgetChar();
            while(pClass==OPERATOR)
            {
                paddChar();
                pgetChar();
            }
            return next_token;
            break;
            
        case PUNCTION:
            next_token.token_type = PUNCTION;
            paddChar();
            pgetChar();
            return next_token;
            break;
            
        case STRING:
            next_token.token_type = STRING;
            paddChar();
            pgetChar();
            while(isStringChar(pnext))
            {
                paddChar();
                pgetChar();
            }
            if(pnext=='\'')
            {
                paddChar();
                pgetChar();
                return next_token;
                break;
            }
            
        case COMMENT://cout<<"error. comments not properly removed";
            break;
            
        case SPACE://cout<< "error. space not properly removed";
            break;
            
        case ERROR: //cout<<"an error occured of type ERROR";
            break;
            
            
    }
    
    

    return next_token;
}



void LexicalAnalysis::paddChar()
{
    if(strcmp(&next,"\n")==0)
    {
        next_token.token_value=next_token.token_value + "\\n";
    }
    else
    {
        next_token.token_value=next_token.token_value + pnext;
    }
    //cout<<"token value is :"<<token.token_value<<"\n";
}

void LexicalAnalysis::pgetChar()
{
    if(str.size()>pctr)
    {
        
        pnext=str.at(pctr);
        pctr++;
        //cout<<"next char is :"<<next<<" \n";
    }
    else
    {
        pClass = ENDOFFILE;
        return;
    }
    
    if (isLetter(pnext))
    {
        //next_token.token_type = LETTER;
        pClass = LETTER;
        return;
    }
    else if(isDigit(pnext))
    {
        //next_token.token_type = DIGIT;
        pClass = DIGIT;
        return;
    }
    else if(pnext=='\'')
    {
        //next_token.token_type = STRING;
        pClass = STRING;
        return;
    }
    else if(isSpace(pnext))
    {
        //token.token_type = SPACE;
        pClass = SPACE;
        return;
    }
    
    else if(isPunction(pnext))
    {
        //next_token.token_type = PUNCTION;
        pClass = PUNCTION;
        return;
    }
    else if(pnext=='/' & str.size()>pctr & str.at(pctr)=='/')
    {
        
        
            //token.token_type = COMMENT;
            pClass = COMMENT;
            return;
        
        
    }
    else if(isOperator(pnext))
    {
        //next_token.token_type = OPERATOR;
        pClass = OPERATOR;
        return;
    }
}



bool LexicalAnalysis::isSpace(char ch)
{
    if(ch == 9 || ch == 32 || ch == 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalysis::isOperator(char ch)
{
    string oper="+,-,*,<,>,&,.,@,/,:,=,~,|,$,!,#,%,^,_,[,],{,},\",`,?";
    bool b=false;
    for(int i=0;i<oper.length();i++)
    {
        if(oper.at(i)==ch)
        {
            b=true;
            //cout<<ch<<" is operator";
            break;
        }
    }
    return b;
}

bool LexicalAnalysis::isPunction(char ch)
{
    if(ch == '(' || ch == ')' || ch == ';' || ch == ',')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalysis::isDigit(char ch)
{
    if(ch > 47 && ch < 58)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalysis::isLetter(char ch)
{
    if((ch > 64 && ch <91) || (ch > 96 && ch <123))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalysis::isCommentChar(char ch)
{
    if(ch=='\"' || isPunction(ch) || ch=='\\' || ch == ' ' || ch == '\t' || isLetter(ch) ||  isDigit(ch) || isOperator(ch))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalysis::isStringChar(char ch)
{
    if(ch=='\"' || isPunction(ch) || ch=='\\' || ch == '\n' || ch == ' ' || ch == '\t' || isLetter(ch) ||  isDigit(ch) || isOperator(ch))
    {
        return true;
    }
    else
    {
        return false;
    }
}

