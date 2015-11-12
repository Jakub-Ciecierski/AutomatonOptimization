//
// Created by dybisz on 11/12/15.
//

#ifndef ACP_CODED_TRANSITION_T_H
#define AC_CODED_TRANSITION_T_H

#include "per_symbol_transition_t.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class CodedTransitionTable: public PerSymbolTransitionTable {
public:
    CodedTransitionTable(string url);
    void print();
    vector<int> getDecodedTransitionTable();

private:
    vector<int> _decodedTransitionTable;
    void _decodeEntries();
    vector<int> _decodeSymbol(int symbol);
    void _printDecoded();
};

#endif //AC_CODED_TRANSITION_T_H
