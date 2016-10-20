//
//  MyVector.h
//  MyVector
//
//  Created by Hao Tan on 9/5/16.
//  Copyright © 2016 Hao Tan. All rights reserved.
//

#ifndef MyVector_h
#define MyVector_h

#include <stdio.h>
#include <memory>

template <typename T>
class MyVector{
public:
    MyVector():elements(nullptr), first_free(nullptr), cap(nullptr) {}
    MyVector(const MyVector&);
    MyVector &operator=(const MyVector&);
    ~MyVector(){free();};
    
    void push_back(const T &t);//bind to any type
    void push_back(T &&t); //move version
    
    void pop_back();
    void reserve(size_t sz);
    bool empty(){return elements == first_free;};
    T& back(){ return *(first_free - 1);};
    T& front(){ return *elements;};
    T& operator[](size_t i){return *(elements + i);};
    
    size_t size(){return first_free - elements;};
    size_t capacity(){return cap - elements;};
    
    T *begin() const {return elements;}
    T *end() const {return first_free;}
    
private:
    static std::allocator<T> alloc; //one copy per class
    T* elements;
    T* first_free;
    T* cap;
    
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void chk_n_alloc(){ if (size() == capacity()) reallocate();};
    void free();
    void reallocate();
    
};



template<typename T>
void MyVector::push_back(const T& t){
    chk_n_alloc();
    alloc.construct(first_free, std::move(t));
}


template<typename T>
void MyVector::push_back(T&& t) {
    chk_n_alloc();
    alloc.construct(first_free, t);
}

template <typename T>
void MyVector::pop_back() {
    if (size() > 0){
        alloc.destroy(first_free--);
    }

}

template<typename T>
void MyVector::reserve(size_t sz) {
    auto cap = capacity();
    if (sz > cap) reallocate();
}




//a helper function for copy and assignment constructor
template<typename T>
std::pair<T*, T*> MyVector::alloc_n_copy(const T *start, const T *end) {
    auto data = alloc.allocate(end-start);//alloc
    return {data, std::uninitialized_copy(start, end, data)};//copy
}


template <typename T>
void MyVector::free() {
    for(auto p = elements; p != cap; p++){
        alloc.destroy(p);
    }
    alloc.deallocate(elements, size());

}




template<typename T>
void MyVector::reallocate(){
    auto sz = size();
    auto new_cap = sz ? 2 * sz : 1;

    auto new_ele = alloc.allocate(new_cap);
    auto dest = new_ele;

    //copy elemts to the new location
    for (auto ele = elements; ele != first_free; ++ele, ++dest) {
        alloc.construct(dest, std::move(*ele));
    }

    elements = new_ele;
    first_free = dest;
    cap = elements + new_cap;

    free();
}




#endif /* MyVector_h */
