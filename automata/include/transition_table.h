//
// Class handles loading/saving automaton from/to a file.
// In addition it presents representation in different types of transition tables.
// Created by dybisz on 11/8/15.
//

#ifndef AC_TRANSITION_TABLE_H
#define AC_TRANSITION_TABLE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "logger.h"
#include "default_transition_t.h"

using namespace std;

class TransitionTable {
public:
    void loadFromFile(string url);
    void print();

private:
    int _numberOfStates;
    int _numberOfSymbols;
    vector<int> _entries;

    void _processInputData(istream& inputFileStream);
    void _loadAndLogNumberOfStates(istream& inputFileStream);
    void _loadAndLogNumberOfSymbols(istream& inputFileStream);
    void _loadAndLogDefaultTransitionTable(istream& inputFileStream);
    int _loadOneSymbolFromFile(istream& inputFileStream);
    void _loadEntries(istream &inputFileStream);
    void _printSpecifications();
    void _printEntries();
};


#endif //_TRANSITION_TABLE_H
