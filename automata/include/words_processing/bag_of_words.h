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

    // Considering available symbols, there is limited number of words,
    // of each length, that can be randomly created.
    // Method gather lengths which were not fill out with words
    // and randomly picks one of them and returns it.
    // When all lengths has been filled, exception is thrown.
    int getRandomAvailableLength(int numberOfSymbols);

    // Only words of length, which falls in interval specified
    // in global_settings.cpp can belong to the bag.
    bool canWordBelongToTheBag(int length);

    int getMinWordLength();

    int getMaxWordLength();

    int numberOfPossibleWords(int numberOfSymbols);

private:
    int _numberOfWords;
    int _minWordLength;
    int _maxWordLength;
    unordered_map<int, vector<Word>> _bag;
    PlotkinBound _plotkinBound;

};

#endif //AC_BAGOFWORDS_H
