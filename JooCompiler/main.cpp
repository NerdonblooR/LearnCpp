#include <iostream>
#include "Lexer.h"

using namespace std;


bool testAutomata(){

    string regex = "d(a|b)*c";
    string toMatch = "c";
    Automata at;
    at.createNFA(TokenType::Identifier, regex);
    at.buildFinalNFA();

    if(!at.match(toMatch)){
        printf("Case: (%s, %s) Success\n", toMatch.c_str(), regex.c_str());
    }else{
        printf("Case: (%s, %s) Fail\n", toMatch.c_str(), regex.c_str());
    }


    toMatch = "dabbc";

    if(at.match(toMatch)){
        printf("Case: (%s, %s) Success\n", toMatch.c_str(), regex.c_str());
    }else{
        printf("Case: (%s, %s) Fail\n", toMatch.c_str(), regex.c_str());
    }

    toMatch = "dc";

    if(at.match(toMatch)){
        printf("Case: (%s, %s) Success\n", toMatch.c_str(), regex.c_str());
    }else{
        printf("Case: (%s, %s) Fail\n", toMatch.c_str(), regex.c_str());
    }


    at.clearAutomata();
    regex = "((\\\\\\*)|a)*";
    toMatch = "\\*a\\*a";

    at.createNFA(TokenType::Identifier, regex);
    at.buildFinalNFA();

    if(at.match(toMatch)){
        printf("Case: (%s, %s) Success\n", toMatch.c_str(), regex.c_str());
    }else{
        printf("Case: (%s, %s) Fail\n", toMatch.c_str(), regex.c_str());
    }


}



int main() {

//    NFAState a(1);
//
//    NFAState b(2);
//
//    NFAState c(3);
//
//    cout << (a == b);
//
//
//    vector<NFAState *> states = {&c,&a,&b};
//
//    vector<int> num = {3,1,2};
//
//    sort(states.begin(), states.end(),NFAStatePtrComp());
//    sort(num.begin(), num.end());
//
//    cout << "Finish";

    //testAutomata();

    string regex = "d(a|b)*c";
    Automata at;
    at.createNFA(TokenType::Identifier, regex);
    at.buildFinalNFA();
    at.buildDFA();
    string toMatch = "c";

    if(at.matchDFA(toMatch)){
        printf("Case: (%s, %s) Success\n", toMatch.c_str(), regex.c_str());
    }else{
        printf("Case: (%s, %s) Fail\n", toMatch.c_str(), regex.c_str());
    }


//    ifstream input("/Users/haotan/Desktop/Projects/compiler/cs444-w17-group17/joo1wCompiler/testInput.txt");
//    stringstream sstr;
//
//    sstr << input.rdbuf();
//
//    int sz = sstr.str().size();
//
//    cout << sstr.str() << endl;
//
//    cout << sstr.str()[sz-2] << endl;
//
//    map<int,Automata*> mp;
//
//
//    if (!mp[1]){
//        cout << "SS" << endl;
//    }



    return 0;
}