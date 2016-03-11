//
//  tree.hpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/7/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


class TreeNode
{
public:
    TreeNode* left;
    TreeNode* right;
    string value;
    int type;
    TreeNode();
    TreeNode(string v);
    TreeNode(int t);
    TreeNode(string v,int t);
    
public:
    void prettyPrint();
    void recPrint(int l);
    void preOrderTraversal();
    void addChild(TreeNode* child);
    
   
    
    
    
    
    
private:
    
};

#endif /* tree_hpp */
