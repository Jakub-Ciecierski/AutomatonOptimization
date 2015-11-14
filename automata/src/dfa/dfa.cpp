//
// Created by dybisz on 11/12/15.
//

#include "dfa.h"

DFA::DFA(string url) : _codedTransitionTable(url) {
    alphabet = _acquireAlphabetFromTransitionTable(_codedTransitionTable);
}

DFA::DFA(int numberOfStates, int numberOfSymbols, vector<int> codedTransitionTable) :
        _codedTransitionTable(numberOfStates, numberOfSymbols, codedTransitionTable) {
    alphabet = _acquireAlphabetFromTransitionTable(_codedTransitionTable);
}

// TODO(dybisz) google test
vector<int> DFA::_acquireAlphabetFromTransitionTable(CodedTransitionTable transitionTable) {
    vector<int> alphabet;

    for (int i = 1; i <= _codedTransitionTable.getNumberOfSymbols(); i++) {
        alphabet.push_back(i);
    }

    return alphabet;
}

int DFA::compute(vector<int> word) {
    return _codedTransitionTable.processWord(word);
}