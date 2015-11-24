//
// Created by dybisz on 11/12/15.
//

#include <utils.h>
#include <clock.h>
#include "coded_transition_t.h"

CodedTransitionTable::CodedTransitionTable(string url) : PerSymbolTransitionTable(url) {
    _codeEntries();
}

CodedTransitionTable::CodedTransitionTable(int numberOfStates, int numberOfSymbols,
                                           vector<int> codedTransitionTable) {
    _numberOfSymbols = numberOfSymbols;
    _numberOfStates = numberOfStates;
    _codedTransitionTable = codedTransitionTable;
    _decodeEntries(codedTransitionTable);
}

void CodedTransitionTable::_decodeEntries(vector<int> codedTransitionTable) {
    int size = _numberOfStates * _numberOfSymbols;
    _entries = utils::initVectorOfMinusOnes(size);

    int shift = 0;
    for (int symbol = 0; symbol < _numberOfSymbols; symbol++) {

        for (int state = 0; state < _numberOfStates; state++) {
            int fromState = (state + 1);
            int toState = codedTransitionTable[state + shift];
            int viaSymbol = (symbol + 1);
            _saveTransitionInEntries(fromState, viaSymbol, toState);
        }
        shift += _numberOfStates;
    }

    LOG_DEBUG("Coded transitionTable: " + utils::vectorToString(codedTransitionTable) + ", decoded to: "
                + utils::vectorToString(_entries));

}

void CodedTransitionTable::_saveTransitionInEntries(int q1, int symbol, int q2) {
    int index = (q1 - 1) * _numberOfSymbols + (symbol - 1);
    _entries[index] = q2;
}


void CodedTransitionTable::_codeEntries() {
    _codedTransitionTable.clear();
    _codedTransitionTable.reserve(_numberOfSymbols * _numberOfStates);

    for (int symbol = 1; symbol <= _numberOfSymbols; symbol++) {
        vector<int> codedSymbol = _codeSymbol(symbol);
        _codedTransitionTable.insert(_codedTransitionTable.end(), codedSymbol.begin(), codedSymbol.end());
    }
}


// TODO(dybisz) google test
vector<int> CodedTransitionTable::_codeSymbol(int symbol) {
    vector<int> codedSymbol;

    for (int r = 1; r <= _numberOfStates; r++) {
        for (int c = 1; c <= _numberOfStates; c++) {
            if (_isTransition(r, symbol, c)) {
                codedSymbol.push_back(c);
                break;
            }
        }
    }
    LOG_DEBUG("symbol [" + to_string(symbol) + "] coded as: " + _symbolToString(codedSymbol));
    return codedSymbol;
}

void CodedTransitionTable::print() {
    _printSpecifications();
    _printCoded();
}

string CodedTransitionTable::_symbolToString(vector<int> symbol) {
    string stringOut = "";
    for (auto i = symbol.begin(); i != symbol.end(); ++i) {
        stringOut += (to_string(*i) + " ");
    }
    return stringOut;
}

void CodedTransitionTable::_printCoded() {
    cout << "Coded automata\n";
    for (auto i = _codedTransitionTable.begin(); i != _codedTransitionTable.end(); ++i) {
        std::cout << *i << ' ';
    }
    cout << endl;
}

vector<int> CodedTransitionTable::getCodedTransitionTable() {
    return _codedTransitionTable;
}

// TODO(dybisz) move this method to TransitionTable (base) class
int CodedTransitionTable::processWord(Word& word) {
    int currentState = 1;

    int len = word.length();

    for (int i = 0; i < len; i++) {
        currentState = _accessTransitionTable(word[i], currentState);
    }

    return currentState;
}
