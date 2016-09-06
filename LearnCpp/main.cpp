//
//  main.cpp
//  LearnCpp
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#include <iostream>
#include <vector>
#include "MyIntVector.hpp"


bool isRectangleCover(std::vector<std::vector<int>>& rectangles){
    //find the bottom left point and the upper right point about the rect
    int area = 0; int contain = 0;
    int bl[2];int ur[2];
    
    if (rectangles.empty()){
        return false;
    }
    
    bl[0] = rectangles[0][0]; bl[1] = rectangles[0][1];
    ur[0] = rectangles[0][2]; ur[1] = rectangles[0][3];
    area = (ur[0] - bl[0]) * (ur[1] - bl[1]);
    for (int i=1; i < rectangles.size(); ++i) {
        area += (rectangles[i][2] - rectangles[i][0]) * (rectangles[i][3] - rectangles[i][1]);
        if (rectangles[i][0] <= bl[0] && rectangles[i][1] <= bl[1]){
            //update bl
            bl[0] = rectangles[i][0];
            bl[1] = rectangles[i][1];
        }
        
        if (rectangles[i][2] >= ur[0] && rectangles[i][3] >= ur[1]){
            ur[0] = rectangles[i][2];
            ur[1] = rectangles[i][3];
        }
        
    }
    
    if (area != (ur[0] - bl[0]) * (ur[1] - bl[1])) return false;
    
    for (int x=bl[0]; x <= ur[0]; ++x){
        for (int y=bl[1]; y <= ur[1]; ++y){
            contain = 0;
            for (int i=1; i < rectangles.size(); ++i) {
                if(x >= rectangles[i][0] && x <= rectangles[i][2] && y >= rectangles[i][1] && y <= rectangles[i][3]){
                    contain = 1;
                    break;
                }
            }
            if (!contain) return false;
        }
    }
    
    return true;
    
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> rects =
    {{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
    
    isRectangleCover(rects);
    //MyVector mv;
    //mv.push_back(1);
    //mv.push_back(2);
    //mv.push_back(3);
    
    //int my_array[3];
    //int sz = &my_array[2] - my_array;
    
    //std::cout << sz << std::endl;
    
    return 0;
}

//define my own vector class