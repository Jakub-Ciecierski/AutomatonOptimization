//
// Created by dybisz on 11/13/15.
//

#ifndef AC_WORDS_GENERATOR_H
#define AC_WORDS_GENERATOR_H

#include <stdexcept>
#include "global_settings.h"
#include "bag_of_words.h"
#include "word.h"

class WordsGenerator {
public:
    int hammingDistance(Word w1, Word w2) const;

private:
    BagOfWords _omegaS;
    BagOfWords _omegaM;
    BagOfWords _omegaL;

    bool _hammingCondition(Word word, int wordLength);
    vector<Word> _getGeneratedWordsOfLength(int length);

    vector<Word> _mergeVectors(vector<Word> v1, vector<Word> v2, vector<Word> v3);
};

#endif //AC_WORDS_GENERATOR_H
