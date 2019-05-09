//
// Created by Hao Tan on 1/16/17.
//

#ifndef JOO1WCOMPILER_TOKEN_H
#define JOO1WCOMPILER_TOKEN_H

#include <string>

using namespace std;

enum TokenType {
    DefaultType,
    WhiteSpace,
    Identifier,
    Keyword,
    IntLiteral,
    FpLiteral,
    BoolLiteral,
    CharLiteral,
    StringLiteral,
    Separator,
    Operator
};

struct Token {

    TokenType t;
    string value;

    Token(TokenType tt, string v): t(tt), value(v){};
};

#endif //JOO1WCOMPILER_TOKEN_H
