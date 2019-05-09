//
// Created by Hao Tan on 1/16/17.
//

#ifndef JOO1WCOMPILER_AUTOMATA_H
#define JOO1WCOMPILER_AUTOMATA_H

#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
//#include <stack>
#include "Token.h"

using namespace std;

/**
 *
 * Base class for both NFAstate and DFAstate for the convenience of compare
 */
struct AtState {
    int myId;
    bool myIsAccept;
    TokenType myTt;

    AtState(int id) : myId(id), myIsAccept(false), myTt(TokenType::DefaultType) {}

    void setAsAccept(TokenType tt) {
        myTt = tt;
        myIsAccept = true;
    }

    bool operator<(const AtState &other) const {
        return myId < other.myId;
    }

    bool operator>(const AtState &other) const {
        return myId > other.myId;
    }

    bool operator==(const AtState &other) const {
        return myId == other.myId;
    }

};

struct NFAState : public AtState {
    map<char, vector<NFAState *> > myTransTable;

    NFAState(int id) : AtState(id), myTransTable() {
    }

    void addTransition(char input, NFAState *s) {
        myTransTable[input].push_back(s);
    }

    vector<NFAState *> move(char input) {
        vector<NFAState *> empty;
        if (myTransTable.find(input) != myTransTable.end()) {
            return myTransTable[input];
        }
        return empty;
    }
};

/**
 *
 * used to construct set of NFAState pointer
 */
struct NFAStatePtrComp {
    bool operator()(const NFAState *lhs, const NFAState *rhs) const {
        /* implement logic here */
        return *lhs < *rhs;
    }
};

struct DFAState : public AtState {
public:

    vector<NFAState *> myNFAStates;

    map<char, DFAState *> myTransTable;

    DFAState(int id, vector<NFAState *> nfaStates) : AtState(id),
                                                     myNFAStates(nfaStates),
                                                     myTransTable() {
        for (auto state : nfaStates) {
            // DFA state token type is the
            // token type of first NFA accept state in its myNFAStates
            if (state->myIsAccept) {
                setAsAccept(state->myTt);
                break;
            }
        }
    }

    DFAState *move(char input) {
        if (myTransTable.find(input) != myTransTable.end()) {
            return myTransTable[input];
        }
        return nullptr;
    }

    void addTransition(char input, DFAState *s) {
        myTransTable[input] = s;
    }

    //override base class operator
    bool operator<(const DFAState &other) const {
        int minSize = min(myNFAStates.size(), other.myNFAStates.size());
        int i = 0;
        for (; myNFAStates[i] == other.myNFAStates[i]; ++i) {
        }
        if (i == minSize) return myNFAStates.size() < other.myNFAStates.size();
        return myNFAStates[i] < other.myNFAStates[i];
    }

    bool operator>(const DFAState &other) const {
        int minSize = min(myNFAStates.size(), other.myNFAStates.size());
        int i = 0;
        for (; myNFAStates[i] == other.myNFAStates[i]; ++i) {
        }
        if (i == minSize) return myNFAStates.size() > other.myNFAStates.size();
        return myNFAStates[i] > other.myNFAStates[i];
    }

    bool operator==(const DFAState &other) const {
        if (myNFAStates.size() != other.myNFAStates.size()) return false;
        for (int i = 0; i < myNFAStates.size(); ++i) {
            if (myNFAStates[i] != other.myNFAStates[i]) return false;
        }
        return true;
    }

};

/**
 *
 * used to construct set of DFAState pointer
 */
struct DFAStatePtrComp {
    bool operator()(const DFAState *lhs, const DFAState *rhs) const {
        /* implement logic here */
        return *lhs < *rhs;
    }
};


class Automata {

public:
    Automata() : nextStateID(0),
                 myInputs(), myOperandStack(),
                 myOperatorStack(), myFinalNFA(), myDFA() {};

    //create an NFA for Token type tt
    bool createNFA(TokenType tt, string regExp);

    //build final NFA for our language
    void buildFinalNFA();

    //return true if the string match the regular expression
    // just for testing the correctness of NFA and DFA
    bool match(string s);

    bool matchDFA(string s);

    //TODO: need to delete all NFAState pointer
    ~Automata() {};

    void clearAutomata() {
        myOperandStack.clear();
        myOperatorStack.clear();
        myInputs.clear();
        nextStateID = 0;

        for (auto nfaptr : myFinalNFA) {
            delete nfaptr;
        }

        myFinalNFA.clear();

    }

    DFAState *moveDFA(char c);

    void restoreDFA() {
        currentState = dfaStart;
    }

    void buildDFA();


private:
    //id of next state
    int nextStateID;
    set<char> myInputs;
    vector<vector<NFAState *> > myOperandStack;
    vector<char> myOperatorStack;
    vector<NFAState *> myFinalNFA;
    vector<DFAState *> myDFA;

    DFAState *dfaStart;
    DFAState *currentState;


    void pushChar(char input);

    bool applyConcat();

    bool applyStar();

    bool applyUnion();

    bool popOperand(vector<NFAState *> &destNfa);

    void eval(char op);

    vector<NFAState *> epsilonClosure(const vector<NFAState *> &states);

    vector<NFAState *> move(const vector<NFAState *> &states, char c);


};

#endif //JOO1WCOMPILER_AUTOMATA_H
