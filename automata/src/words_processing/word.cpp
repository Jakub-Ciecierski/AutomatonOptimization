//
// Created by dybisz on 11/13/15.
//

#include "word.h"

Word::Word() {}

Word::Word(vector<int> word) {
    _entries.swap(word);
}

Word::Word(int word[]) {
    // TODO(dybisz) change it
    cout << "i chuj" << endl;
}

void Word::appendSymbol(int symbol) {
    _entries.push_back(symbol);
}

int Word::length() const{
    return _entries.size();
}

string Word::toString() {
    return utils::vectorToString(_entries);
}

void Word::clear() {
    _entries.clear();
}

int Word::operator[](int i) const {
    return _entries[i];
}

int &Word::operator[](int i) {
    return _entries[i];
}