//
// Created by Hao Tan on 1/16/17.
//

#ifndef JOO1WCOMPILER_LEXER_H
#define JOO1WCOMPILER_LEXER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include "Automata.h"


using namespace std;

class Lexer {
public:
    Lexer(string inputFileName) : at(), buffer(), lexemeBegin(0), forward(0) {
        //initialize buffer
        ifstream input(inputFileName);
        stringstream sstr;
        sstr << input.rdbuf();
        buffer = sstr.str();
        initializeAutomata();
    };


    Token* getNext(); // get next Token

private:
    string buffer;
    //start
    int lexemeBegin;
    //end
    int forward;
    ifstream inputFile;
    Automata at;
    void initializeAutomata();
};

#endif //JOO1WCOMPILER_LEXER_H
