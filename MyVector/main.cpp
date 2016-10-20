//
//  main.cpp
//  MyVector
//
//  Created by Hao Tan on 2014-11-13.
//  Copyright (c) 2014 Hao Tan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "MyIntVector.hpp"

struct Trie{
public:
    char c;
    std::vector<char> values;
    Trie(): c(), values() {}
};


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


int longestSubstring(std::string s, int k) {
    if (s.size() == 0 || k > s.size()) return 0;
    if (k == 0) return s.size();

    int fqTable[26] = {};
    for (char& c :  s){
        fqTable[c - 'a'] += 1;
    }

    int rlen = 0;
    for (int i = 0; i < s.size(); ++i){
        if (fqTable[s[i] - 'a'] < k){
            break;
        }
        rlen++;
    }

    if (rlen == s.size()) return rlen;

    int left = longestSubstring(s.substr(0, rlen), k);
    int right = longestSubstring(s.substr(rlen+1), k);

    return std::max(left,right);

}

int main(int argc, const char * argv[]) {
    //int a = longestSubstring("aaabb", 3);
    //int my_array[3];
    //int sz = &my_array[2] - my_array;
    Trie a;

    
    std::cout << a.c << std::endl;
    
    return 0;
}

//define my own vector class