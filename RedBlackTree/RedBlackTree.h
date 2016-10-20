//
// Created by Hao Tan on 10/19/16.
//

#ifndef MYVECTOR_REDBLACKTREE_H
#define MYVECTOR_REDBLACKTREE_H

#include <iostream>

struct RedBlackTreeNode{
    int key;
    int value;
    int colour;
    RedBlackTreeNode* left;
    RedBlackTreeNode* right;
    RedBlackTreeNode* parent;
};

#endif //MYVECTOR_REDBLACKTREE_H
