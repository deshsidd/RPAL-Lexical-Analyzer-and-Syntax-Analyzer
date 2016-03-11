//
//  parser.cpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/6/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#include "parser.hpp"
#include "scanner.hpp"
#include "tree.hpp"
#include <string.h>





SyntaxAnalysis::SyntaxAnalysis(string s):la(s)
{
    nt=la.scan();
    //cout<<"first token is :"<<nt.token_value<<endl;
    stack<TreeNode* > stk;
    stackend=new TreeNode("stackend",-1);
    addStackEnd(); // adds stackend token onto stack
}

void SyntaxAnalysis::BuildTree(string s,int num)
{
    
    TreeNode* n=new TreeNode(s,num);
    
    if(!(stk.size()>num))
    {
        cout<<"error. stack overflow! \n";
        exit (EXIT_FAILURE);
    }
    else
    {
        
        //cout<<"adding tree :"<<s<<endl;
        TreeNode* first=new TreeNode();
        first=removeTop();
        TreeNode* selected=new TreeNode();
        selected=first;
        
        for(int i=1;i<num;i++)
        {
            TreeNode* next=new TreeNode();
            next=removeTop();
            next->right=selected;
            selected=next;
        }
        n->left=selected;
        stk.push(n);
        //cout<<"size of stack now is :"<<stk.size()-1<<"\n";
    }
    
}

void SyntaxAnalysis::BuildNode(string s, int n)
{
    string value;
    if(s=="true" || s=="false" || s=="nil" || s=="dummy")
    {
        value="<"+s+">";
    }
    else if(n==Token::LETTER)
    {
        value="<ID:"+s+">";
    }
    else if(n==Token::DIGIT)
    {
        value="<INT:"+s+">";
    }
    else if(n==Token::STRING)
    {
        value="<STR:"+s+">";
    }
    
    TreeNode* tn=new TreeNode(value,n);
    //cout<<"adding node :"<<value<<" on stack"<<endl;
    stk.push(tn);
}

void SyntaxAnalysis::read(string s)
{
    
    if(s!=nt.token_value)
    {
        cout<<"error expected "<<s<<" but found "<<nt.token_value;
        exit (EXIT_FAILURE);
    }
    //cout<<"read token :"<<s<<endl;
    /*
    if(nt.token_type==0 || nt.token_type==1 || nt.token_type==3)
    {
        BuildTree(s,0);
    }
     */
    //do
    //{
        nt= la.scan(); //NT always one token ahead
    //cout<<"scanned token :"<<nt.token_value<<endl;
    //}while(nt.token_type!=Token::PUNCTION);
}

void SyntaxAnalysis::parse()
{
    E();
    if(stk.size() != 2)
    {
        cout <<"error. parsing finished with more than one node on stack\n";
        exit (EXIT_FAILURE);
    }
    if(nt.token_type != Token::ENDOFFILE)
    {
        cout << "error. parsing finished but input still remaining/n";
        exit (EXIT_FAILURE);
    }
    //cout<<"EXPECTED AST : \n\n";
    //cout<<expected;
    //cout<<"\n\n";
    //cout<<"PRINTING AST : \n\n";
    
    //cout<<"\nparsing complete.\n";

}

void SyntaxAnalysis::printAST()
{
    stk.top()->prettyPrint();
}

bool SyntaxAnalysis::isReservedWord(string str)
{
    bool b=false;
    string reserved_words[] = { "in", "where", ".", "aug", "and", "or", "&", "not", "gr", "ge", "ls", "le", "eq", "ne", "+", "-", "*", "/", "**", "@", "within", "=", "rec", "let", "fn"};
    for(int i=0;i<25;i++)
    {
        if(reserved_words[i]==str)
        {
            b=true;
            break;
        }
    }
    return b;
}

void SyntaxAnalysis::addStackEnd()
{
    stk.push(stackend);
}


TreeNode* SyntaxAnalysis::removeTop()
{
    TreeNode* temp=new TreeNode();
    if(!(stk.top()->value.compare("stackend")==0 && stk.top()->type==-1))
    {
        //cout<<"removing node :"<<stk.top()->value<<" from stack\n";
        temp=stk.top();
        stk.pop();
        return temp;
    }
    else
    {
        //cout<<"error. reached the end of stack.";
        exit (EXIT_FAILURE);
    }
    
}
//EEEEEEEEEEEEEEEEEE
//EEEEEEEEEEEEEEEEEE
//EEEEEEEEEEEEEEEEEE
void SyntaxAnalysis::E()
{
    //cout<<"Running E()\n";
    if(nt.token_value=="let")
    {
        read("let");
        D();
        read("in");
        E();
        BuildTree("let",2);
    }
    else if(nt.token_value=="fn")
    {
        read("fn");
        int n=0;
        do
        {
            Vb();
            n++;
        }while(nt.token_type==Token::LETTER || nt.token_value=="(");
        read(".");
        E();
        BuildTree("lambda",n+1);
    }
    else
    {
        Ew();
    }
    //cout<<"Returning from E()\n";
    return;
    
}
//EwEwEwEwEwEwEwEwEwEwEwEw
//EwEwEwEwEwEwEwEwEwEwEwEw
//EwEwEwEwEwEwEwEwEwEwEwEW
void SyntaxAnalysis::Ew()
{
    //cout<<"Running Ew()\n";
    T();
    if(nt.token_value=="where")
    {
        read("where");
        Dr();
        BuildTree("where",2);
    }
    //cout<<"Returning from Ew()\n";
    return;
}
//TTTTTTTTTTTTTTTTTTT
//TTTTTTTTTTTTTTTTTTT
//TTTTTTTTTTTTTTTTTTT
void SyntaxAnalysis::T()
{
    //cout<<"Running T()\n";
    Ta();
    if(nt.token_value==",")//chk//
    {
        int n=0;
        do
        {
            read(",");
            Ta();
            n++;
        }while(nt.token_value==",");
        BuildTree("tau", n+1);
    }
    //cout<<"Returning from T()\n";
    return;
}

//TaTaTaTaTaTaTaTaTaTa
//TaTaTaTaTaTaTaTaTaTa
//TaTaTaTaTaTaTaTaTaTa
void SyntaxAnalysis::Ta()
{
    //cout<<"Running Ta()\n";
    Tc();
    while(nt.token_value=="aug")
    {
        read("aug");
        Tc();
        BuildTree("aug", 2);
    }
    //cout<<"Returning from Ta()\n";
    return;
}

//TcTcTcTcTcTcTcTcTcTcTc
//TcTcTcTcTcTcTcTcTcTcTc
//TcTcTcTcTcTcTcTcTcTcTc
void SyntaxAnalysis::Tc()
{
    //cout<<"Running Tc()\n";
    B();
    if(nt.token_value=="->")
    {
        read("->");
        Tc();
        read("|");
        Tc();
        BuildTree("->", 3);
    }
    //cout<<"Returning from Tc()\n";
    return;
}

//BBBBBBBBBBBBBBBBBBB
//BBBBBBBBBBBBBBBBBBB
//BBBBBBBBBBBBBBBBBBB
void SyntaxAnalysis::B()
{
    //cout<<"Running B()\n";
    Bt();
    while(nt.token_value=="or")
    {
        read("or");
        Bt();
        BuildTree("or", 2);
    }
    //cout<<"Returning from B()\n";
    return;
}
//BtBTBtBtBtBtBtBtBtBtBt
//BtBtBtBtBtBtBtBtBtBtBt
//BtBtBtBtBtBtBtBtBtBtBt
void SyntaxAnalysis::Bt()
{
    //cout<<"Running Bt()\n";
    Bs();
    while(nt.token_value=="&")
    {
        read("&");
        Bs();
        BuildTree("&", 2);
    }
    //cout<<"Returning from Bt()\n";
    return;
}

//BsBsBsBsBsBsBsBsBsBsBs
//BsBsBsBsBsBsBsBsBsBsBs
//BsBsBsBsBsBsBsBsBsBsBs
void SyntaxAnalysis::Bs()
{
    //cout<<"Running Bs()\n";
    if(nt.token_value=="not")
    {
        read("not");
        Bp();
        BuildTree("not", 1);
    }
    else
    {
        Bp();
    }
    //cout<<"Returning from Bs()\n";
    return;
}

//BpBpBpBpBpBpBpBpBpBp
//BpBpBpBpBpBpBpBpBpBp
//BpBpBpBpBpBpBpBpBpBp
void SyntaxAnalysis::Bp()
{
    //cout<<"Running Bp()\n";
    A();
    if(nt.token_value=="gr" || nt.token_value==">")
    {
        read(nt.token_value);
        A();
        BuildTree("gr",2);
    }
    else if(nt.token_value=="ge" || nt.token_value==">=")
    {
        read(nt.token_value);
        A();
        BuildTree("ge",2);
    }
    else if(nt.token_value=="ls" || nt.token_value=="<")
    {
        read(nt.token_value);
        A();
        BuildTree("ls",2);
    }
    else if(nt.token_value=="le" || nt.token_value=="<=")
    {
        read(nt.token_value);
        A();
        BuildTree("le",2);
    }
    else if(nt.token_value=="eq" )
    {
        read(nt.token_value);
        A();
        BuildTree("eq",2);
    }
    else if(nt.token_value=="ne" )
    {
        read(nt.token_value);
        A();
        BuildTree("ne",2);
    }
    //cout<<"Returning from Bp()\n";
    return;
}

//AAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAA
void SyntaxAnalysis::A()
{
    //cout<<"Running A()\n";
    if(nt.token_value=="-")
    {
        read("-");
        At();
        BuildTree("neg", 1);
    }
    else if(nt.token_value=="+")
    {
        read("+");
        At();
    }
    else
    {
        At();
    }
    while(nt.token_value=="+" || nt.token_value=="-")//chk//
    {
        string temp=nt.token_value;
        read(nt.token_value);
        At();
        BuildTree(temp, 2);
    }
    //cout<<"Returning from A()\n";
    return;
}

//AtAtATAtAtAtAtAtAtAtAtAt
//AtAtATAtAtAtAtAtAtAtAtAt
//AtAtATAtAtAtAtAtAtAtAtAt
void SyntaxAnalysis::At()
{
    //cout<<"Running At()\n";
    Af();
    while(nt.token_value=="*" || nt.token_value=="/")
    {
        string temp=nt.token_value;
        read(nt.token_value);
        Af();
        BuildTree(temp, 2);
    }
    //cout<<"Returning from At()\n";
    return;
}

//AfAfAfAfAfAfAfAfAfAfAfAf
//AfAfAfAfAfAfAfAfAfAfAfAf
//AfAfAfAfAfAfAfAfAfAfAfAf
void SyntaxAnalysis::Af()
{
    //cout<<"Running Af()\n";
    Ap();
    if(nt.token_value=="**")
    {
        read("**");
        Af();
        BuildTree("**", 2);
    }
    //cout<<"Returning from Af()\n";
    return;
}

//ApApApApApApApApApApApAp
//ApApApApApApApApApApApAp
//ApApApApApApApApApApApAp
void SyntaxAnalysis::Ap()
{
    //cout<<"Running Ap()\n";
    R();
    while(nt.token_value=="@")
    {
        read("@");
        BuildNode(nt.token_value, nt.token_type);//chk//
        read(nt.token_value);
        R();
        BuildTree("@", 3);
    }
    //cout<<"Returning from Ap()\n";
    return;
    
}
//RRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRR
void SyntaxAnalysis::R()
{
    //cout<<"Running R()\n";
    Rn();
    while((nt.token_type==Token::LETTER || nt.token_type==Token::DIGIT || nt.token_type==Token::STRING || nt.token_value=="true" || nt.token_value=="false" || nt.token_value=="nil" || nt.token_value=="(" || nt.token_value=="dummy" ) && !isReservedWord(nt.token_value))
    {
        Rn();
        BuildTree("gamma", 2);
    }
    //cout<<"Returning from R()\n";
    return;
}

//RnRnRnRnRnRnRnRnRnRnRnRn
//RnRnRnRnRnRnRnRnRnRnRnRn
//RnRnRnRnRnRnRnRnRnRnRnRn
void SyntaxAnalysis::Rn()
{
    //cout<<"Running Rn()\n";
    if(nt.token_type==Token::LETTER)//ckh//
    {
        BuildNode(nt.token_value, nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_type==Token::DIGIT)
    {
        BuildNode(nt.token_value, nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_type==Token::STRING)
    {
        BuildNode(nt.token_value, nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_value=="true")
    {
        BuildNode("true", nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_value=="false")
    {
        BuildNode("false", nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_value=="nil")
    {
        BuildNode("nil", nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_value=="dummy")
    {
        BuildNode("dummy", nt.token_type);
        read(nt.token_value);
    }
    else if(nt.token_value=="(" && nt.token_type==Token::PUNCTION)
    {
        read("(");
        E();
        read(")");
    }
    else
    {
        //cout<<"token not recognized\n";
    }
    //cout<<"Returning from Rn()\n";
    return;
}

//DDDDDDDDDDDDDDDDDDDDDD
//DDDDDDDDDDDDDDDDDDDDDD
//DDDDDDDDDDDDDDDDDDDDDD
void SyntaxAnalysis::D()
{
    //cout<<"Running D()\n";
    Da();
    if(nt.token_value=="within")
    {
        read("within");
        D();
        BuildTree("within", 2);
    }
    //cout<<"Returning from D()\n";
    return;
}

//DaDaDaDaDaDaDaDaDaDaDaDa
//DaDaDaDaDaDaDaDaDaDaDaDa
//DaDaDaDaDaDaDaDaDaDaDaDa
void SyntaxAnalysis::Da()
{
    //cout<<"Running Da()\n";
    Dr();
    if(nt.token_value=="and")
    {
        int n=0;
        do
        {
            read("and");
            Dr();
            n++;
            
        }while(nt.token_value=="and");
        BuildTree("and", n+1);
    }
    //cout<<"Returning from Da()\n";
    return;
}

//DrDrDrDrDrDrDrDrDrDrDrDr
//DrDrDrDrDrDrDrDrDrDrDrDr
//DrDrDrDrDrDrDrDrDrDrDrDr
void SyntaxAnalysis::Dr()
{
    //cout<<"Running Dr()\n";
    if(nt.token_value=="rec")
    {
        read("rec");
        Db();
        BuildTree("rec", 1);
    }
    else
    {
        Db();
    }
    //cout<<"Returning from Dr()\n";
    return;
}

//DbDbDbDbDbDbDbDbDbDbDbDb
//DbDbDbDbDbDbDbDbDbDbDbDb
//DbDbDbDbDbDbDbDbDbDbDbDb
void SyntaxAnalysis::Db()//chk//
{
    //cout<<"Running Db()\n";
    nnt=la.peek();
    if(nt.token_value=="(")
    {
        read("(");
        D();
        read(")");
    }
    else if(nt.token_type==Token::LETTER)
    {
        if(nnt.token_value=="=" || nnt.token_value==",")
        {
            Vl();
            read("=");
            E();
            BuildTree("=", 2);
        }
        else
        {
            BuildNode(nt.token_value, nt.token_type);//chk//
            read(nt.token_value);
            int n=0;
            do
            {
                Vb();
                n++;
            }while(nt.token_type==Token::LETTER || nt.token_value=="(");
            read("=");
            E();
            BuildTree("function_form", n+2);
        
        }
    }
    else
    {
        cout<<"error in Db\n";
    }
    //cout<<"Returning from Db()\n";
    return;
}

//VbVbVbVbVbVbVbVbVbVbVbVbVbVb
//VbVbVbVbVbVbVbVbVbVbVbVbVbVb
//VbVbVbVbVbVbVbVbVbVbVbVbVbVb
void SyntaxAnalysis::Vb()
{
    //cout<<"Running Vb()\n";
    if(nt.token_value=="(")
    {
        read("(");
        if(nt.token_value==")")
        {
            read(")");
            BuildNode("()", nt.token_type);//chk//
        }
        else
        {
            Vl();
            read(")");
        }
    }
    else if(nt.token_type==Token::LETTER)//chk//
    {
        BuildNode(nt.token_value, nt.token_type);
        read(nt.token_value);
    }
    else
    {
        cout<<"error in Vb";
    }
    //cout<<"Returning from Vb()\n";
    return;
}

//VlVlVlVlVlVlVlVlVlVlVlVlVl
//VlVlVlVlVlVlVlVlVlVlVlVlVl
//VlVlVlVlVlVlVlVlVlVlVlVlVl
void SyntaxAnalysis::Vl()//chk//
{
    //cout<<"Running Vl()\n";
    BuildNode(nt.token_value, nt.token_type);
    read(nt.token_value);
    if(nt.token_value==",")
    {
        int n=0;
        do
        {
            read(",");
            BuildNode(nt.token_value, nt.token_type); //chk//
            read(nt.token_value);
            n++;
        }while(nt.token_value==",");
        BuildTree(",", n+1);
    }
    //cout<<"Returning from Vl()\n";
    return;
}
