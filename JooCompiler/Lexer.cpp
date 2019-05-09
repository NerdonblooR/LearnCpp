//
// Created by Hao Tan on 1/16/17.
//

#include "Lexer.h"


Token* Lexer::getNext() {
    //implement maximal munch
    if (lexemeBegin == buffer.size()){
        return nullptr;
    }

    at.restoreDFA();//restore to start state
    DFAState *lastMatched;
    DFAState *walker;

    int lastMatchedEnd = lexemeBegin;

    for(;;){
        walker = at.moveDFA(buffer[forward++]);
        while (walker){
            if (walker->myIsAccept){
                lastMatchedEnd = forward;
                lastMatched = walker;
            }
            walker = at.moveDFA(forward++);
        }

        if (!lastMatched){
            //report error, unrecognized input
            //throw exception

        }

        if (lastMatched){
            int matchLen = lastMatchedEnd - lexemeBegin;
            string matched = buffer.substr(lexemeBegin, lastMatchedEnd);

            forward = lastMatchedEnd;
            lexemeBegin = lastMatchedEnd;

            if (lastMatched->myTt == TokenType::WhiteSpace){
                //do nothing
            }else{
                Token* t = new Token(lastMatched->myTt,matched);
                return t;
            }
        }
    }
}


void Lexer::initializeAutomata() {

}