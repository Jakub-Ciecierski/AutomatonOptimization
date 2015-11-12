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
    int compute(vector<int> word);

private:
    CodedTransitionTable _codedTransitionTable;
};

#endif //AC_AUTOMATON_H
