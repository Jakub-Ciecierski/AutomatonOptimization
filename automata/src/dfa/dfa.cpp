//
// Created by dybisz on 11/12/15.
//

#include <utils.h>
#include <clock.h>
#include "dfa.h"

DFA::DFA(string url) : _codedTransitionTable(url) {
    _loadAndLogAlphabet(_codedTransitionTable);
}

DFA::DFA(int numberOfStates, int numberOfSymbols, vector<int> codedTransitionTable) :
        _codedTransitionTable(numberOfStates, numberOfSymbols, codedTransitionTable) {
    _loadAndLogAlphabet(_codedTransitionTable);
}

DFA::DFA(const DFA& dfa) :
        _codedTransitionTable(dfa.getCodedTransitionTable()){
    _loadAndLogAlphabet(_codedTransitionTable);
}

CodedTransitionTable DFA::getCodedTransitionTable() const{
    return this->_codedTransitionTable;
}

void DFA::_loadAndLogAlphabet(CodedTransitionTable codedTransitionTable) {
    alphabet = _acquireAlphabetFromTransitionTable(_codedTransitionTable);
    //LOG_INFO("Alphabet loaded: " + utils::vectorToString(alphabet));
}

// TODO(dybisz) google test
vector<int> DFA::_acquireAlphabetFromTransitionTable(CodedTransitionTable transitionTable) {
    vector<int> alphabet;

    for (int i = 1; i <= _codedTransitionTable.getNumberOfSymbols(); i++) {
        alphabet.push_back(i);
    }

    return alphabet;
}

int DFA::compute(Word& word) {
    return _codedTransitionTable.processWord(word);
}

bool DFA::checkRelationInducedByLanguage(Word& w1, Word& w2) {
    int state1 = compute(w1);
    int state2 = compute(w2);

    return (state1 == state2);
}