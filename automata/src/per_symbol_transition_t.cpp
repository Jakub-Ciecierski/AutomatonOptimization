//
// Created by dybisz on 11/12/15.
//

#include "per_symbol_transition_t.h"

PerSymbolTransitionTable::PerSymbolTransitionTable() { }
PerSymbolTransitionTable::PerSymbolTransitionTable(string url) : StandardTransitionTable(url) { }

bool PerSymbolTransitionTable::operator()(int state1, int symbol, int state2) {
    try {
        return _isTransition(state1, symbol, state2);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what());
    }

    return true;
}

bool PerSymbolTransitionTable::_isTransition(int state1, int symbol, int state2) {
    int resultState = _accessTransitionTable(symbol, state1);
    return (resultState == state2);
}

void PerSymbolTransitionTable::print() {
    _printSpecifications();
    _printEntries();
}

void PerSymbolTransitionTable::_printEntries() {
    try {
        cout << "Per Symbol Transition Tables: " << endl;

        for (int symbol = 1; symbol <= _numberOfSymbols; symbol++) {
            _printPerSymbolTransitionTable(symbol);
        }

    }
    catch (std::exception &e) {
        LOG_ERROR(e.what());
    }
}

void PerSymbolTransitionTable::_printPerSymbolTransitionTable(int symbol) {
    cout << "[symbol " << symbol << "]\n";

    for (int r = 1; r <= _numberOfStates; r++) {
        for (int c = 1; c <= _numberOfStates; c++) {
            string entry = (_isTransition(r, symbol, c)) ? "1" : "0";
            cout << entry << " ";
        }
        cout << endl;
    }
}