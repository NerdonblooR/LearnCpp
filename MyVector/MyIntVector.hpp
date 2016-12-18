//
//  MyVector.hpp
//  MyVector
//
//  Created by Hao Tan on 8/11/16.
//  Copyright © 2016 Hao Tan. All rights reserved.
//

#ifndef MyIntVector_hpp
#define MyIntVector_hpp

#include <stdio.h>
#include <memory>


class MyIntVector{
public:
    MyIntVector():elements(nullptr), first_free(nullptr), cap(nullptr) {}
    MyIntVector(const MyIntVector&);
    MyIntVector &operator=(const MyIntVector&);
    ~MyIntVector(){free();};
    
    void push_back(int i);
    void pop_back();
    void reserve(size_t sz);
    bool empty(){return elements == first_free;};
    int back(){return *(first_free - 1);};
    int front(){return *elements;};
    int operator[](size_t i){return *(elements + i);};
    
    size_t size(){return first_free - elements;}
    size_t capacity(){return cap - elements;}
    
    int *begin() const {return elements;}
    int *end() const {return first_free;}

private:
    static std::allocator<int> alloc; //one copy per class
    int* elements;
    int* first_free;
    int* cap;
    
    std::pair<int*, int*> alloc_n_copy(const int*, const int*);
    void chk_n_alloc(){ if (size() == capacity()) reallocate();};
    void free(); 
    void reallocate();
    
};




#endif /* MyVector_hpp */
