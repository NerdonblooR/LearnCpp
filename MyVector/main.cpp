//
//  main.cpp
//  MyVector
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#include <iostream>
#include "MyVector.hpp"



int main(int argc, const char * argv[]) {

    MyVector<int> intVector;
    int a = 3;
    int b = 4;
    intVector.push_back(a);
    intVector.push_back(b);

    std::cout << intVector[0] << std::endl;
    std::cout << intVector[1] << std::endl;


    return 0;
}

//define my own vector class