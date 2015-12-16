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

/*
 * Due to the fact, that project focuses on words, something more flexible
 * and transparent was needed Instead of vector of integers. Class provides
 * overloaded operators, along with different ways of creating words.
 * One can also get length, clear words or convert it into string.
 */
class Word {
private:
    // Contains actual word. Nothing more than a sequenc of integers.
    // No need to allow user to use it publicaly - apppropriate
    // operators have been provided to access its content.
    vector<int> _entries;

public:
    // User can either make empty word and append letter by letter to it
    // or create one based on provided data structure. Available ones
    // (for now) are vector and array of integers.
    Word();
    Word(vector<int> word);
    Word(int word[]);

    // Appends one symbol at the end of the word.
    void appendSymbol(int symbol);

    // Auxiliary methods for user convenient:
    // getting up to date length, clearing all symbols in the words
    // and converting it to the string (usefull in debugging process).
    int length() const;
    void clear();
    string toString();

    // Two type of access operators have been overloaded:
    // first make a copy of some particular entry of index i,
    // second one returns reference to the entry.
    int operator[](int i) const;
    int &operator[](int i);
};

#endif //ACPROJECT_WORD_H
