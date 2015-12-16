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

/*
 * Data structure, which pack set of supplied words sorted by length.
 * It was useful during testing process, particulary when we were checking
 * bahaviour of the algorithm on different, distinct sets of input data,
 * with the need of coparision using measurement based on hamming condition.
 */
class BagOfWords {
public:

    // User is able to either create empty data structur or to a priori
    // decide about words lengths. When the latter has been chose, bag is
    // automatically filled up with empty sets of all lengths from <min,max>
    BagOfWords();
    BagOfWords(int minWordLength, int maxWordLength);

    // Add word to the class. Length is calculated and placed under
    // appropriate key.
    void addWord(Word word);

    // user can either acquire words of given length or
    // all of them. For example he/she can take all of them and change
    // into pairs for fitness funtion evaluation.
    vector<Word> getWordsOfLength(int length);
    vector<Word> getAllWords();

    // Auxiliary method for printing words as a string. Useful during
    // debug of the application
    static string wordsToString(vector<Word> words);

    int size();

    // Only words of length, which falls in interval specified
    // in global_settings.cpp can belong to the bag.
    bool canWordBelongToTheBag(int length);

    // Getters, setters of lenths parameters
    int getMinWordLength();
    int getMaxWordLength();

    // Prints content of the class, sorted by length
    void print();

private:
    // Set of parameters used during computation of the class
    // It contains info about total number of words currently stored
    // their minimum, maximum  length and a unordered map to
    // sort them according to lengths.
    int _numberOfWords;
    int _minWordLength;
    int _maxWordLength;

    // Core of the class. Contains set of words sorted according to lengths.
    unordered_map<int, vector<Word>> _bag;
};

#endif //AC_BAGOFWORDS_H
