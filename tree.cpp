//
//  tree.cpp
//  rpal
//
//  Created by Siddhant Deshmukh on 3/7/16.
//  Copyright © 2016 Siddhant Deshmukh. All rights reserved.
//

#include "tree.hpp"

TreeNode::TreeNode()
{
    value="";
    type=-1;
    left=NULL;
    right=NULL;
    //ast="";
}

TreeNode::TreeNode(string v)
{
    value=v;
    type=-1;
    left=NULL;
    right=NULL;
    //ast="";
}

TreeNode::TreeNode(int t)
{
    value="";
    type=t;
    left=NULL;
    right=NULL;
    //ast="";
}

TreeNode::TreeNode(string v, int t)
{
    value=v;
    type=t;
    left=NULL;
    right=NULL;
    //ast="";
}

void TreeNode::addChild(TreeNode*  child)
{
    if(left == NULL)
    {
        left = child;
    }
    else
    {
        TreeNode *temp = left;
        while(temp->right != NULL)
        {
            temp = temp->right;
        }
        temp->right = child;
    }
}

void TreeNode::prettyPrint()
{
    int level=0;
    recPrint(level);
}

void TreeNode::recPrint(int l)
{
    for(int i=0;i<l;i++)
    {
        
        cout<<".";
    }
   
    cout<<value<<"\n";
    if(left !=NULL)
    {
        left->recPrint(l+1);
    }
    if(right !=NULL)
    {
        right->recPrint(l);
    }
}


