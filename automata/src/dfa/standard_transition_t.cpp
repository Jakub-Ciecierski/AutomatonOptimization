//
// Created by dybisz on 11/12/15.
//

#include "standard_transition_t.h"


StandardTransitionTable::StandardTransitionTable() { }

StandardTransitionTable::StandardTransitionTable(string url) : TransitionTable(url) { }


int StandardTransitionTable::operator()(int symbol, int state) {
    int resultState;
    try {
        resultState = _accessTransitionTable(symbol, state);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what());
    }
    return resultState;
}

void StandardTransitionTable::print() {
    _printSpecifications();
    _printEntries();
}

int StandardTransitionTable::_accessTransitionTable(int& symbol, int& state) {
    if (symbol < 1 || symbol > _numberOfSymbols) {
        throw invalid_argument("symbol out of range <=> (symbol < 0 || symbol > _numberOfSymbols)");
    }

    if (state < 1 || state > _numberOfStates) {
        string s = "";
        s += "state out of ranges <=> (state < 0 || state > _numberOfStates) ";
        s += "state: ";
        s += to_string(state);
        throw invalid_argument(s);
    }

    int index = (state - 1) * _numberOfSymbols + (symbol - 1);

    return _entries[index];
}

void StandardTransitionTable::_printEntries() {
    try {
        cout << "Standard Transition Table: " << endl;
        _printStandardTransitionTable();
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what());
    }
}

void StandardTransitionTable::_printStandardTransitionTable() {
    for (int r = 1; r <= _numberOfStates; r++) {
        for (int c = 1; c <= _numberOfSymbols; c++) {
            cout << _accessTransitionTable(c, r) << " ";
        }
        cout << endl;
    }
}