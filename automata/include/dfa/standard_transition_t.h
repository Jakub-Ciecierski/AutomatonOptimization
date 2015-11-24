//
// Created by dybisz on 11/12/15.
//

#ifndef AC_STANDARD_TRANSITION_T_H
#define AC_STANDARD_TRANSITION_T_H

#include "transition_table.h"
#include <iostream>
#include <stdexcept>

class StandardTransitionTable: public TransitionTable {
public:
    StandardTransitionTable();
    StandardTransitionTable(string url);
    void print();
    int operator()(int symbol, int state);

protected:
    int _accessTransitionTable(int& symbol, int& state);
    void _printEntries();
    void _printStandardTransitionTable();
};

#endif //AC_STANDARD_TRANSITION_T_H
