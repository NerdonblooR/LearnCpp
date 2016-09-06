//
//  Node.h
//  LearnCpp
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#ifndef __LearnCpp__Node__
#define __LearnCpp__Node__

#include <stdio.h>

template<class T>
class Node{
public:
    Node();
    Node(const T& content, Node<T> *prev = NULL, Node<T> *next = NULL);
    T data;
    Node<T>* get_next_node();
    Node<T>* get_prev_node();
    void delete_self();
    void insert_after(Node<T> *ptr);
    
    
private:
    Node<T> *_next;
    Node<T> *_prev;
};

#endif /* defined(__LearnCpp__Node__) */
