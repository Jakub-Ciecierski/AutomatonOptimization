//
// Created by dybisz on 11/12/15.
//

#ifndef AC_AUTOMATON_H
#define AC_AUTOMATON_H

#include "coded_transition_t.h"
#include <vector>

class DFA {
public:
    DFA(string url);
    DFA(int numberOfStates, int numberOfSymbols, vector<int> codedTransitionTable);

    // symbols take values from interval [1; _numberOfSymbols]
    vector<int> alphabet;
    int compute(vector<int> word);

private:
    vector<int> _acquireAlphabetFromTransitionTable(CodedTransitionTable);
    CodedTransitionTable _codedTransitionTable;
};

#endif //AC_AUTOMATON_H