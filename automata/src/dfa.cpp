//
// Created by dybisz on 11/12/15.
//

#include "dfa.h"

DFA::DFA(string url) : _codedTransitionTable(url) {}

int DFA::compute(vector<int> word) {
    return _codedTransitionTable.processWord(word);
}