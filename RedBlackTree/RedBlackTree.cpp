//
// Created by Hao Tan on 10/19/16.
//

#include "RedBlackTree.h"

//initialize a Red
RedBlackTree::RedBlackTree(): root(NULL){
    nil = new RedBlackTreeNode();
}

void RedBlackTree::insert(RedBlackTreeNode* node){
    RedBlackTreeNode *walker = root;
    RedBlackTreeNode *p = nil;

    while(walker != nil){
        p = walker;
        if(node->key < walker->key){
            walker = walker->left;
        }else{
            walker  = walker->right;
        }
    }

    if (p == nil){
        root = node;
    }else if (node->key < p->key ){
        p->left = node;
    }else{
        p->right = node;
    }

    node->parent = p;
    node->left = nil;
    node->right = nil;
    node->color = 0;//assign colour red
    fixUpTree(node);
}

void RedBlackTree::fixUpTree(RedBlackTreeNode* node){
    RedBlackTreeNode* walker = node;
    while(!walker->parent->color){//loop until node parent's color is black
        RedBlackTreeNode* grandp = walker->parent->parent;
        RedBlackTreeNode* uncle;
        if(walker->parent == grandp->left){
            uncle = grandp->right;
            if (!uncle->color){//uncle is red
                walker->parent->color = 1; //set parent to black
                uncle->color = 1; //set uncle to black
                grandp->color = 0; //set grandpa to red
                walker = grandp;
            }else{
                if (walker->parent->right = walker){
                    walker = walker->parent;
                    leftRotate(walker);
                }
                walker->parent->color = 1;
                walker->parent->parent->color = 0;
                rightRotate(walker->parent->parent);
            }
        }else{//node parent is right child of grand parent
            uncle = grandp->left;
            if (!uncle->color){
                walker->parent->color = 1;
                uncle->color = 1;
                grandp->color = 0;
                walker = grandp;
            }else{
                if(walker->parent->left = walker){
                    walker = walker->parent;
                    rightRotate(walker);
                }
                walker->parent->color = 1;
                walker->parent->parent->color = 0;
                leftRotate(walker->parent->parent);
            }
        }
    }
    root.color = 1;
}

void RedBlackTree::leftRotate(RedBlackTreeNode* node){
    RedBlackTreeNode* rightChild = node->right;
    node->right = rightChild->left;
    if(rightChild->left != nil) rightChild->left->parent = node;
    rightChild->left = node;
    rightChild->parent = node->parent;

    //update node's parent info
    if (node->parent == nil){
        root = rightChild;
    }
    else if(node->parent->right == node){
        node->parent->right = rightChild;
    }else{
        node->parent->left = rightChild;
    }

    node->parent = rightChild;
}

void RedBlackTree::rightRotate(RedBlackTreeNode* node){
    RedBlackTreeNode* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nil) leftChild->right->parent = node;
    leftChild->parent = node->parent;
    leftChild->right = node;


    if(node->parent == nil){
        root = leftChild;
    }else if(node->parent->right == node){
        node->parent->right = leftChild;
    }else{
        node->parent->left = leftChild;
    }
    node->parent = leftChild;
}

