//
//  main.cpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/6/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "scanner.hpp"
#include "token.hpp"
#include "parser.hpp"

/*
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
 
 */

void testPrettyPrint();
void testScanner(string s);
void testParser(string s);
void testCommandLine();
void usage();
int main(int argc, const char * argv[])
{
    //string str="let a,b = 3,4 in Print( a)";
    //testPrettyPrint();
    //testCommandLine();
    
    //testScanner(str);
    //testParser(str);
   
    bool ast=false;
    bool l=false;
    bool file=false;
    bool fileopen=false;
    ifstream f;

    

    if(argc==1 || argc>3)
    {
        usage();
    }

    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i],"-ast")==0)
        {
            ast=true;
        }
        else if(strcmp(argv[i],"-l")==0)
        {
            l=true;
        }
        else
        {
            file=true;
            f.open(argv[i]);
            if(f.is_open())
            {
                fileopen=true;
            }
        }
    }

    //////////////////
    ////START////////
    ////////////////
    if(!file || !fileopen)
    {
        cout<<"ERROR:INCORRECT FILE NAME OR PARAMETER\n";
        exit (EXIT_FAILURE);
    }
    string str((istreambuf_iterator<char>(f)),istreambuf_iterator<char>());
    
        SyntaxAnalysis s(str);
        s.parse();
        if(ast)
        {
            s.printAST();
        }
        if(l)
        {
            cout<<str;
        }
   
    
    //cout<<str;
    /*
    cout<<"ast is :"<<ast<<"\n";
    cout<<"l is :"<<l<<"\n";
    cout<<"file is :"<<file<<"\n";
    cout<<"fileopen is :"<<fileopen<<"\n";
    */

    
    return 0;
}



void testPrettyPrint()
{
    SyntaxAnalysis s("Print((fn f. f 2) (fn x. x eq 1 -> 1 | x+2))");
    
    TreeNode* root=new TreeNode("root");
    TreeNode* rleft=new TreeNode("rleft");
    TreeNode* rright=new TreeNode("rright");
    TreeNode* one=new TreeNode("one");
    TreeNode* two=new TreeNode("two");
    TreeNode* three=new TreeNode("three");
    TreeNode* four=new TreeNode("four");
    root->left=rleft;
    root->right=rright;
    rleft->left=one;
    rleft->right=two;
    rright->left=three;
    rright->right=four;
    root->prettyPrint();
}

void testScanner(string str)
{
    LexicalAnalysis l (str);
    Token token;
    Token ntoken;
    
    while(!(token.token_type==Token::ENDOFFILE))
    {
        token=l.scan();
        //ntoken=l.peek();
        cout<<"token value  : "<<token.token_value<<" type:"<<token.token_type<<"\n";
        //cout<<"token type returned from scanner is : "<<token.token_type<<"\n";
        //cout<<"next token value  : "<<ntoken.token_value<<" type:"<<ntoken.token_type<<"\n";
        //cout<<"next token type returned from scanner is : "<<ntoken.token_type<<"\n";
        
    }
    
}

void testCommandLine()
{
    /*
    ifstream f;
    if(!(argc==3))
    {
        cout<<"error. number of arguments";
        exit (EXIT_FAILURE);
    }
    if(strcmp("-ast",argv[1])==0)
    {
        f.open(argv[2]);
        if(!(f.is_open()))
        {
            cout<<"error. file not opened properly";
            exit (EXIT_FAILURE);
        }
    }
    else
    {
        cout<<"error. -ast needed";
        exit (EXIT_FAILURE);
    }
     */
}

void testParser(string str)
{
    string expected="";
    SyntaxAnalysis s(str);
    s.parse();
    //cout<<expected;
    
   
}

void usage()
{
    cout<<"USAGE: "<<"./pl [-ast] [-l] filename\n";
}
