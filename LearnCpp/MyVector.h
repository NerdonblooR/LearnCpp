//
//  MyVector.h
//  LearnCpp
//
//  Created by Hao Tan on 9/5/16.
//  Copyright © 2016 Hao Tan. All rights reserved.
//

#ifndef MyVector_h
#define MyVector_h

template <typename T>
class MyVector{
public:
    MyVector():elements(nullptr), first_free(nullptr), cap(nullptr) {}
    MyVector(const MyVector&);
    MyVector &operator=(const MyVector&);
    ~MyVector(){free();};
    
    void push_back(const T &t) //bind to any type
    void push_back(T &&t); //move version
    
    void pop_back();
    void reserve(size_t sz);
    bool empty(){return elements == first_free;};
    T& back();
    T& front();
    T& operator[](size_t i);
    
    size_t size();
    size_t capacity();
    
    T *begin() const {return elements;}
    T *end() const {return first_free;}
    
private:
    static std::allocator<int> alloc; //one copy per class
    T* elements;
    T* first_free;
    T* cap;
    
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void chk_n_alloc(){ if (size() == capacity()) reallocate();};
    void free();
    void reallocate();
    
};




#endif /* MyVector_h */
