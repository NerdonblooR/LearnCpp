//
//  main.cpp
//  MyVector
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#include <iostream>
#include "MyVector.hpp"

int hammingDistance(int a, int b){
    int diff = a ^ b;
    int mask = 1;
    int dist = 0;
    while (diff != 0){
        dist += diff & mask;
        diff = diff >> 1;
    }
    return dist;
}


int main(int argc, const char * argv[]) {

    MyVector<int> intVector;
    MyVector<int> intVector2;

    int a = 3;
    int b = 4;
    intVector.push_back(a);
    intVector.push_back(b);

    for (auto elem : intVector) {
        std::cout << elem << std::endl;
    }

    intVector.pop_back();

    for (auto elem : intVector) {
        std::cout << elem << std::endl;
    }

    std::cout << hammingDistance(4,2) << std::endl;


    return 0;
}

//define my own vector class