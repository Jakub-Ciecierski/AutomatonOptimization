//
// Created by root on 11/12/15.
//

#include "default_transition_t.h"

void DefaultTransitionTable::setEntries(vector<int> entries, int numberOfStates, int numberOfSymbols) {
    _numberOfStates = numberOfStates;
    _numberOfSymbols = numberOfSymbols;
    _entries.swap(entries);
}

void DefaultTransitionTable::print() {

}