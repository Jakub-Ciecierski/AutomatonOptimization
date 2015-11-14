//
// Created by dybisz on 11/13/15.
//

#ifndef AC_WORD_H
#define AC_WORD_H

#include <vector>
#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

class Word {
private:
    vector<int> _entries;

public:
    Word();

    Word(vector<int> word);

    Word(int word[]);

    void appendSymbol(int symbol);

    int length();

    string toString();

    void clear();

    int operator[](int i) const;

    int &operator[](int i);
};

#endif //ACPROJECT_WORD_H
