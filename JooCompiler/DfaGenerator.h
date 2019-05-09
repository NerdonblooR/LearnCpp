#ifndef JOO1WCOMPILER_DFAGENERATOR_H
#define JOO1WCOMPILER_DFAGENERATOR_H

#define EPSILON_CHAR '\0'

#include <array>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
#include "Token.h"
#include "Automata.h" 

struct DFAState{
    char Id;
    TokenType TType;
    bool IsAccepting;
};

std::array<char, 3> InputSymbols = {
	'a'
	, 'b'
	, 'c'
};

class DfaGenerator {
private: 
	std::set<NFAState*> EpsilonClosure (std::set<NFAState*> startStates);
	std::set<NFAState*> Move (std::set<NFAState*> startStates, char input);
	bool ProcessState(DFAState* dfaState, NFAState* nfaState, std::set<NFAState*> processedStates); 
public: 
	std::map<std::pair<DFAState*, char>, std::set<DFAState*> > GenerateDfa(NFAState* startState);	
};

#endif 
