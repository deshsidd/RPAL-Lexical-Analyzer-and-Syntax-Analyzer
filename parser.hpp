//
//  parser.hpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/6/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp


#include <iostream>
#include <string>
#include <stack>
#include "scanner.hpp"
#include "token.hpp"
#include "tree.hpp"
#include <sstream>

using namespace std;

class SyntaxAnalysis
{
public:
    stack<TreeNode* > stk;
private:
    LexicalAnalysis la;
    Token nt;
    Token nnt;
    
    TreeNode* stackend;
    
public:
    SyntaxAnalysis(string input);
    void read(string s);
    void BuildTree(string s,int n);
    void BuildNode(string s,int n);
    bool isReservedWord(string str);
    void addStackEnd();
    TreeNode* removeTop();
    void parse();
    void printAST();
    
    
    
private:
    void E();
    void Ew();
    
    void T();
    void Ta();
    void Tc();
    
    void B();
    void Bt();
    void Bs();
    void Bp();
    
    void A();
    void At();
    void Af();
    void Ap();
    
    void R();
    void Rn();
    
    void D();
    void Da();
    void Dr();
    void Db();
    
    void Vb();
    void Vl();
};

#endif /* parser_hpp */
