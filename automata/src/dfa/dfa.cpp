//
// Created by dybisz on 11/12/15.
//

#include <util/utils.h>
#include "dfa.h"

DFA::DFA(string url) : _codedTransitionTable(url) {
    _loadAndLogAlphabet(_codedTransitionTable);
}

DFA::DFA(int numberOfStates, int numberOfSymbols, vector<int> codedTransitionTable) :
        _codedTransitionTable(numberOfStates, numberOfSymbols, codedTransitionTable) {
    _loadAndLogAlphabet(_codedTransitionTable);
}

void DFA::_loadAndLogAlphabet(CodedTransitionTable codedTransitionTable) {
    alphabet = _acquireAlphabetFromTransitionTable(_codedTransitionTable);
    LOG_INFO("Alphabet loaded: " + utils::vectorToString(alphabet));
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

