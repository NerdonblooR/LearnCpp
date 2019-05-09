#include "DfaGenerator.h"

using namespace std; 

std::set<NFAState*> EpsilonClosure (std::set<NFAState*> startStates) {
	std::stack<NFAState*> stateStack; 
	set<NFAState*> returnSet; 

	// push all start states into stack 
	for (set<NFAState*>::iterator it = startStates.begin(); it != startStates.end(); ++it) {
		stateStack.push(*it);
		returnSet.insert(*it);
	}

	// process all elements in stack 
	while (stateStack.size() > 0) {
		NFAState* currentState = stateStack.top();
		stateStack.pop();

		// find epsilon-transitions for current state 
		if (currentState->myTransTable.count(EPSILON_CHAR) > 0) 	{ // key exists
			for (int j = 0; j < currentState->myTransTable.at(EPSILON_CHAR).size(); ++j) {
				NFAState* childState = currentState->myTransTable.at(EPSILON_CHAR).at(j); 

				std::set<NFAState*> currentStateSet = EpsilonClosure(std::set<NFAState*> {currentState}); 
				
				if (currentStateSet.find(childState) == currentStateSet.end()) {	// childstate not in e-closure(currentState)
					returnSet.insert(childState);
					stateStack.push(childState); 
				}
			}
		}	
	}

	return returnSet;
}

std::set<NFAState*> Move (std::set<NFAState*> startStates, char input) {
	std::set<NFAState*> returnSet; 

	for (std::set<NFAState*>::iterator it = startStates.begin(); it != startStates.end(); ++it) {

		// find character-transitions for current state 
			if ((*it)->myTransTable.count(input) > 0) 	{ // key exists
				for (int j = 0; j < (*it)->myTransTable.at(input).size(); ++j) {
					returnSet.insert((*it)->myTransTable.at(input).at(j));
				}
			}
	}

	return EpsilonClosure(returnSet);
}

DFAState* ConvertToDFA(NFAState * nfaState) {
	DFAState* returnState = new DFAState(); 
	returnState->Id = nfaState->myId; 
	returnState->TType = nfaState->myTt; 
	returnState->IsAccepting = nfaState->myIsAccept;

	return returnState;  
}

bool ProcessState(DFAState* dfaState, NFAState* nfaState, std::set<NFAState*> processedStates) {
	if (processedStates.count(nfaState) != 0) {
		return false; 
	}

	dfaState = ConvertToDFA(nfaState); 

	processedStates.insert(nfaState); 

	return true; 
}

std::map<std::pair<DFAState*, char>, std::set<DFAState*> > GenerateDfa(NFAState* startState) {
	std::map<std::pair<DFAState*, char>, std::set<DFAState*> > returnMap; 

	std::set<NFAState*> processedStates; 

	std::set<NFAState*> nfaStates = EpsilonClosure(set<NFAState*> {startState});

	while (nfaStates.begin() != nfaStates.end()) {		// TODO: need to test
		NFAState* currentNfaState = *(nfaStates.begin()); 
		DFAState* currentDfaState = NULL; 

		// if nfa state not yet processed 
		if (ProcessState(currentDfaState, currentNfaState, processedStates)) {
			for (int i = 0; i < InputSymbols.size(); i++) {
				
				set<NFAState*> eClosureStates = EpsilonClosure(Move(set<NFAState*> {currentNfaState}, InputSymbols[i]));
				
				nfaStates.insert(eClosureStates.begin(), eClosureStates.end()); 

				std::set<DFAState*> eClosureStatesDfa; 

				for (std::set<NFAState*>::iterator eClosureStatesIt = eClosureStates.begin(); 
					eClosureStatesIt != eClosureStates.end(); 
					++eClosureStatesIt) {
						eClosureStatesDfa.insert(ConvertToDFA(*eClosureStatesIt));
				}

				returnMap[std::pair<DFAState*, char>(currentDfaState, InputSymbols[i])] = eClosureStatesDfa; 
			}
		}
		else {	// if nfa state already processed 
			nfaStates.erase(currentNfaState);
		}
	}

	return returnMap; 
}
