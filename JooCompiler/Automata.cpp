//
// Created by Hao Tan on 1/16/17.
//

#include "Automata.h"

bool Automata::popOperand(vector<NFAState *> &destNfa) {
    if (!myOperandStack.empty()) {
        destNfa.insert(destNfa.begin(), myOperandStack.back().begin(), myOperandStack.back().end());
        myOperandStack.pop_back();
        return true;
    }

    return false;
}

void Automata::pushChar(char input) {
    NFAState *s0 = new NFAState(nextStateID++);
    NFAState *s1 = new NFAState(nextStateID++);

    s0->addTransition(input, s1);

    vector<NFAState *> nfa = {s0, s1};

    myOperandStack.push_back(nfa);
    myInputs.insert(input);
}


bool Automata::applyConcat() {

    vector<NFAState *> nfa0, nfa1;
    if (!popOperand(nfa1) || !popOperand(nfa0)) return false;

    nfa0.back()->addTransition(0, nfa1[0]);
    //add entire nfa1 to nfa0
    nfa0.insert(nfa0.end(), nfa1.begin(), nfa1.end());

    myOperandStack.push_back(nfa0);

    return true;

}


bool Automata::applyStar() {
    vector<NFAState *> nfa;
    if (!popOperand(nfa)) return false;

    NFAState *start = new NFAState(nextStateID++);
    NFAState *end = new NFAState(nextStateID++);


    start->addTransition(0, nfa[0]);
    start->addTransition(0, end);

    nfa.back()->addTransition(0, nfa[0]);
    nfa.back()->addTransition(0, end);


    nfa.insert(nfa.begin(), start);
    nfa.push_back(end);

    myOperandStack.push_back(nfa);

    return true;

}


bool Automata::applyUnion() {
    vector<NFAState *> nfa0, nfa1;
    if (!popOperand(nfa1) || !popOperand(nfa0)) return false;

    NFAState *start = new NFAState(nextStateID++);
    NFAState *end = new NFAState(nextStateID++);

    start->addTransition(0, nfa0[0]);
    start->addTransition(0, nfa1[0]);


    nfa0.back()->addTransition(0, end);
    nfa1.back()->addTransition(0, end);

    nfa0.insert(nfa0.end(), nfa1.begin(), nfa1.end());

    nfa0.insert(nfa0.begin(), start);
    nfa0.push_back(end);


    myOperandStack.push_back(nfa0);

    return true;
}


bool Automata::createNFA(TokenType tt, string regExp) {
    bool lastIsChar = false;
    for (auto it = regExp.begin(); it != regExp.end(); ++it) {
        switch (*it) {
            case '*': {
                lastIsChar = true;
                eval(*it); //evaluate star immediately
            }
                break;

            case '|': {
                lastIsChar = false;
                myOperatorStack.push_back('|');
            }
                break;

            case '(': {
                if (lastIsChar) myOperatorStack.push_back('.');
                lastIsChar = false;
                myOperatorStack.push_back('(');
            }
                break;

            case ')': {
                //pop operator from operator stack until we see "("
                char top = myOperatorStack.back();
                while (top != '(') {
                    eval(top);
                    myOperatorStack.pop_back();
                    top = myOperatorStack.back();
                }
                myOperatorStack.pop_back();//pop "("
            }
                break;
            case '\\': {
                //escape char
                it++;
                if (lastIsChar) myOperatorStack.push_back('.');
                pushChar(*it);
                lastIsChar = true;
            }
                break;

            default: {
                if (lastIsChar) myOperatorStack.push_back('.');
                pushChar(*it);
                lastIsChar = true;
            }
                break;
        }

    }
    //eval until myOperator stack is empty
    //top of the operand should be the final NFA
    while (!myOperatorStack.empty()) {
        char op = myOperatorStack.back();
        eval(op);
        myOperatorStack.pop_back();
    }

    NFAState *lastState = myOperandStack.back().back();
    lastState->setAsAccept(tt);

    return true;
}

void Automata::eval(char op) {
    switch (op) {
        case '.':
            applyConcat();
            break;
        case '*':
            applyStar();
            break;
        case '|':
            applyUnion();
            break;
    }
}

/**
 * call this function only when we have created NFAs for
 * all types of tokens need to be supported for our language
 */
void Automata::buildFinalNFA() {
    NFAState *start = new NFAState(nextStateID++);
    myFinalNFA.push_back(start);
    //add epsilon transition to all NFA start states in the operand stack
    for (auto it = myOperandStack.begin(); it != myOperandStack.end(); ++it) {
        start->addTransition(0, (*it)[0]);
        //add all states to my final NFA
        myFinalNFA.insert(myFinalNFA.end(), it->begin(), it->end());
    }

}

bool Automata::match(string s) {
    vector<NFAState *> currentState;
    currentState.push_back(myFinalNFA[0]);
    currentState = epsilonClosure(currentState);

    for (auto cit = s.begin(); cit != s.end(); ++cit) {
        currentState = epsilonClosure(move(currentState, *cit));
    }

    for (auto state = currentState.begin(); state != currentState.end(); ++state) {
        if ((*state)->myIsAccept) {
            return true;
        }
    }
    return false;
}

bool Automata::matchDFA(string s) {
    currentState = dfaStart;

    for (auto c : s){
        if (currentState->move(c)){
            currentState = currentState->move(c);
        }else{
            break;
        }
    }
    return currentState->myIsAccept;
}


DFAState* Automata::moveDFA(char c) {
    DFAState *nextState = currentState->move(c);
    if(nextState){
        currentState = nextState;
    }
    return nextState;

}

void Automata::buildDFA() {

    set<DFAState *, DFAStatePtrComp> createdState; //set of created DFA states
    vector<DFAState *> toConstruct; //DFA states not yet full constructed

    vector<NFAState *> nfaStates = {myFinalNFA[0]};
    nfaStates = epsilonClosure(nfaStates);


    DFAState *start = new DFAState(nextStateID++, nfaStates);

    myDFA.push_back(start);
    toConstruct.push_back(start);
    createdState.insert(start);
    dfaStart = start;

    while (!toConstruct.empty()) {
        DFAState *s = toConstruct.back();
        toConstruct.pop_back(); // this state is fully constructed;

        for (auto c: myInputs) {

            nfaStates = epsilonClosure(move(s->myNFAStates, c));
            if (!nfaStates.empty()){//move destination is empty
                DFAState *destState = new DFAState(nextStateID++, nfaStates);//create a new DFAState

                auto stateIt = createdState.find(destState);

                if (stateIt == createdState.end()) {
                    //we have not created an identical DFA state
                    createdState.insert(destState);
                    //need to construct it later
                    toConstruct.push_back(destState);
                    s->addTransition(c, destState);

                } else {
                    nextStateID--;
                    s->addTransition(c, *stateIt);
                }
            }


        }

    }
};

vector<NFAState *> Automata::move(const vector<NFAState *> &states, char c) {
    vector<NFAState *> result;
    set<int> stateIdInResult;

    for (auto state = states.begin(); state != states.end(); ++state) {
        vector<NFAState *> dest = (*state)->move(c);

        for (auto ds = dest.begin(); ds != dest.end(); ++ds) {
            if (stateIdInResult.find((*ds)->myId) == stateIdInResult.end()) {
                result.push_back(*ds);
                stateIdInResult.insert((*ds)->myId);
            }
        }
    }
    return result;
}

vector<NFAState *> Automata::epsilonClosure(const vector<NFAState *> &states) {
    vector<NFAState *> eClosure = states;
    vector<NFAState *> stack = states;
    set<int> stateIdInClosure;

    for (int i = 0; i < eClosure.size(); ++i) {
        stateIdInClosure.insert(eClosure[i]->myId);
    }

    NFAState *s;
    vector<NFAState *> dest;
    while (!stack.empty()) {
        s = stack.back();
        stack.pop_back();

        dest = s->move(0);
        for (auto ds = dest.begin(); ds != dest.end(); ++ds) {
            //not in the set
            if (stateIdInClosure.find((*ds)->myId) == stateIdInClosure.end()) {
                eClosure.push_back(*ds);
                stack.push_back(*ds);
                stateIdInClosure.insert((*ds)->myId);
            }
        }

    }

    sort(eClosure.begin(), eClosure.end(), NFAStatePtrComp()); //must sort to make DFA comparison work
    return eClosure;
}


