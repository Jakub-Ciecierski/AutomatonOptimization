//
// Created by root on 11/12/15.
//

#ifndef AC_DEFAULT_TRANSITION_T_H
#define AC_DEFAULT_TRANSITION_T_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class DefaultTransitionTable {
public:
    void setEntries(vector<int> entries, int numberOfStates, int numberOfSymbols);
    void print();

private:
    int _numberOfStates;
    int _numberOfSymbols;
    vector<int> _entries;

};

#endif //ACPROJECT_DEFAULT_TRANSITION_T_H
