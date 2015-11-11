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

using namespace std;

class TransitionTable {

public:
    void loadFromFile(string url);

private:
    int _numberOfStates;
    int _numberOfSymbols;
    int** _defaultTransitionTable;

    void _processInputData(istream& inputFileStream);
    int _loadOneSymbolFromFile(istream& inputFileStream);
    int** _loadDefaultTransitionTable(istream &inputFileStream);
    void _deleteDefaultTransitionTable();
};


#endif //_TRANSITION_TABLE_H
