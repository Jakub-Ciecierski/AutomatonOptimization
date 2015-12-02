//
// Created by dybisz on 11/13/15.
//

#ifndef AC_BAGOFWORDS_H
#define AC_BAGOFWORDS_H

#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <string>
#include "word.h"
#include "plotkin_bound.h"

using namespace std;

// Manages set of words, sorted by length
class BagOfWords {
public:
    BagOfWords();

    BagOfWords(int minWordLength, int maxWordLength);

    void addWord(Word word);

    vector<Word> getWordsOfLength(int length);

    vector<Word> getAllWords();

    void print();

    static string wordsToString(vector<Word> words);

    int size();

    // Only words of length, which falls in interval specified
    // in global_settings.cpp can belong to the bag.
    bool canWordBelongToTheBag(int length);

    int getMinWordLength();

    int getMaxWordLength();

private:
    int _numberOfWords;
    int _minWordLength;
    int _maxWordLength;
    unordered_map<int, vector<Word>> _bag;
};

#endif //AC_BAGOFWORDS_H
