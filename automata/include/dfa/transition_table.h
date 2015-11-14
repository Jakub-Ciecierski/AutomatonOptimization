//
// Class handles loading/saving automaton from/to a file.
// It constitutes base for more specialized transition tables.
// Created by dybisz on 11/8/15.
//

#ifndef AC_TRANSITION_TABLE_H
#define AC_TRANSITION_TABLE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include "logger.h"

using namespace std;

class TransitionTable {
public:
    TransitionTable();
    TransitionTable(string url);
    void print();
    int getNumberOfSymbols();

protected:
    int _numberOfStates;
    int _numberOfSymbols;
    vector<int> _entries;
    void _printSpecifications();
    string _entriesToString();
    void _printEntries();

private:
    void _processInputData(istream& inputFileStream);
    void _loadAndLogNumberOfStates(istream& inputFileStream);
    void _loadAndLogNumberOfSymbols(istream& inputFileStream);
    void _loadAndLogDefaultTransitionTable(istream& inputFileStream);
    int _loadOneSymbolFromFile(istream& inputFileStream);
    void _loadEntries(istream &inputFileStream);
};


#endif //_TRANSITION_TABLE_H
