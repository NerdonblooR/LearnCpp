//
// Created by Hao Tan on 10/19/16.
//

#ifndef MYVECTOR_REDBLACKTREE_H
#define MYVECTOR_REDBLACKTREE_H

#include <iostream>

struct RedBlackTreeNode {
    int key;
    int value;
    int colour;/*red=0, black=1*/
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;
    RedBlackTreeNode *parent;

    RedBlackTreeNode() : key(0), value(0), colour(1), left(), right(), parent() {};
};

class RedBlackTree {
public:
    RedBlackTree() : root(), nil() {
        nil = new RedBlackTreeNode();
        root = nil;
    }; //what if I do not use new here
    RedBlackTree(const RedBlackTree &source); //copy constructor
    ~RedBlackTree();

    void insert(const int key, const int value);

    void insert(const RedBlackTreeNode &node);

    void deleteNode(const int key);

    void deleteNode(const RedBlackTreeNode &node);

    RedBlackTreeNode &lookup(int key);

    /*friend functions*/
    friend std::ostream &operator<<(std::ostream &os, const RedBlackTree &);

private:
    void leftRotation(RedBlackTreeNode *node);

    void rightRotation(RedBlackTreeNode *node)

    );

    void fixUpTree(RedBlackTreeNode *node);

    RedBlackTreeNode *root;
    RedBlackTreeNode *nil; //this could be set as static
};

#endif //MYVECTOR_REDBLACKTREE_H
