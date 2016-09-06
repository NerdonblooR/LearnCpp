//
//  Node.cpp
//  LearnCpp
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#include "Node.h"

template<class T>
Node<T>::Node(){
    
}


template<class T>
Node<T>::Node(const T &content, Node<T> *prev, Node<T> *next){
    if(prev != NULL)prev->_next = this;
    if(next != NULL)next->_prev = this;
    this->data = content;
    this->_prev = prev;
    this->_next = next;
}


template<class T>
Node<T>* Node<T>::get_next_node(){
    return this->_next;
}


template<class T>
Node<T>* Node<T>::get_prev_node(){
    return this->_prev;
}

template<class T>
void Node<T>::insert_after(Node<T> *ptr){
    if(ptr == NULL) return;
    this->_next = ptr;
    ptr->_prev = this;
    
}


template<class T>
void Node<T>::delete_self(){
    if(this->_prev != NULL){
        this->_prev->_next = this->_next;
    }
    
    if(this->_next != NULL){
        this->_next->prev = this->_prev;
    }
    
}