//
// Created by dybisz on 11/12/15.
//

#include "coded_transition_t.h"

CodedTransitionTable::CodedTransitionTable(string url) : PerSymbolTransitionTable(url) {
    _decodeEntries();
}

void CodedTransitionTable::_decodeEntries() {
    _decodedTransitionTable.clear();
    _decodedTransitionTable.reserve(_numberOfSymbols * _numberOfStates);

    for (int symbol = 1; symbol <= _numberOfSymbols; symbol++) {
        vector<int> decodedSymbol = _decodeSymbol(symbol);
        _decodedTransitionTable.insert(_decodedTransitionTable.end(), decodedSymbol.begin(), decodedSymbol.end());
    }
}

vector<int> CodedTransitionTable::_decodeSymbol(int symbol) {
    vector<int> decodedSymbol;
    for(int r = 1; r <= _numberOfStates; r++) {
        for(int c = 1; c <= _numberOfStates; c++) {
            if(_isTransition(r,symbol,c)) {
                decodedSymbol.push_back(c);
                break;
            }
        }
    }

    return decodedSymbol;
}

void CodedTransitionTable::print() {
    _printSpecifications();
    _printDecoded();
}

void CodedTransitionTable::_printDecoded() {
    cout << "Decoded automata\n";
    for (auto i = _decodedTransitionTable.begin(); i != _decodedTransitionTable.end(); ++i) {
        std::cout << *i << ' ';
    }
    cout << endl;
}

vector<int> CodedTransitionTable::getDecodedTransitionTable() {
    return _decodedTransitionTable;
}
