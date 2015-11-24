//
// Created by dybisz on 11/12/15.
//

#ifndef AC_CODED_TRANSITION_T_H
#define AC_CODED_TRANSITION_T_H

#include "per_symbol_transition_t.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "word.h"

class CodedTransitionTable: public PerSymbolTransitionTable {
public:
    CodedTransitionTable(string url);
    CodedTransitionTable(int numberOfStates, int numberOfSymbols, vector<int> codedTransitionTable);
    void print();
    vector<int> getCodedTransitionTable();
    int processWord(Word& word);

private:
    vector<int> _codedTransitionTable;
    void _decodeEntries(vector<int> codedTransitionTable);
    void _codeEntries();
    vector<int> _codeSymbol(int symbol);
    string _symbolToString(vector<int> symbol);
    void _printCoded();

    void _saveTransitionInEntries(int state, int symbol, int toState);
};

#endif //AC_CODED_TRANSITION_T_H
