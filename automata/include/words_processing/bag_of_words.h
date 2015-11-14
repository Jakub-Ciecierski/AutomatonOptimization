//
// Created by dybisz on 11/13/15.
//

#ifndef AC_BAGOFWORDS_H
#define AC_BAGOFWORDS_H

#include <unordered_map>
#include <string>
#include "word.h"

using namespace std;

// Manages set of words, sorted by length
class BagOfWords {
public:
    BagOfWords();

    void addWord(Word word);

    vector<Word> getWordsOfLength(int length);

    void print();

    string wordsToString(vector<Word> words);

    int size();

private:
    int _numberOfWords;
    unordered_map<int, vector<Word>> _bag;
};

#endif //AC_BAGOFWORDS_H
