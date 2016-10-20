//
//  MyIntVector.cpp
//  MyVector
//
//  Created by Hao Tan on 8/11/16.
//  Copyright © 2016 Hao Tan. All rights reserved.
//

#include "MyIntVector.hpp"

std::allocator<int> MyIntVector::alloc; //if we dont declare alloc here, each transaltion unit will have its own copy.

MyIntVector::MyIntVector(const MyIntVector& mv){
    auto p = alloc_n_copy(mv.begin(), mv.end());
    elements = p.first;
    first_free = p.second;
    cap = p.second;
}

MyIntVector&
MyIntVector::operator=(const MyIntVector& mv){
    //free the memory first
    free();
    auto p = alloc_n_copy(mv.begin(), mv.end());
    elements = p.first;
    first_free = p.second;
    cap = p.second;
    return *this; //what is the type of this?
}


void
MyIntVector::push_back(int i){
    chk_n_alloc();
    *first_free = i; //use alloc.construct when push back object
    first_free++;
    return;
}

void
MyIntVector::pop_back(){
    auto itr = first_free--;
    alloc.destroy(itr);
    return;
}

void
MyIntVector::reserve(size_t sz){
    auto newdata = alloc.allocate(sz);
    //update pointers
    elements = newdata;
    cap = elements + sz;
    first_free = elements;
}

void
MyIntVector::free(){
    for (auto itr=elements; itr != cap; ++itr) {
        alloc.destroy(itr);
    }
    alloc.deallocate(elements, size());

}


//return the new start and end pointer for the vector
//helper function for the copy and assignment constructor
std::pair<int*, int*>
MyIntVector::alloc_n_copy(const int *b, const int *e){
    auto data = alloc.allocate(b - e);
    //uninitialized copy return the iterator past the last element
    return {data, std::uninitialized_copy(b, e, data)};
}

void
MyIntVector::reallocate(){
    //double the size or fixed size
    auto sz = size();
    auto newcapacity = sz? 2*sz : 1;
    auto newdata = alloc.allocate(newcapacity);

    auto dest = newdata;
    //using move operator here to copy is better, but for int, it might make no differene,
    //fundamental types has no constructor. only class member has constructor
    for (auto elms=elements; elms != first_free; ++elms, ++dest)
        alloc.construct(dest, std::move(*elms));
 
    free();
    
    //update pointers
    elements = newdata;
    cap = elements + newcapacity;
    first_free = dest;
}
