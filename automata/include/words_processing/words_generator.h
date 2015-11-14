//
// Created by dybisz on 11/13/15.
//

#ifndef AC_WORDS_GENERATOR_H
#define AC_WORDS_GENERATOR_H

#include <stdexcept>
#include "global_settings.h"
#include "bag_of_words.h"
#include "word.h"
#include "utils.h"
#include <util/logger.h>

using namespace global_settings;

class WordsGenerator {
public:
    WordsGenerator(vector<int> alphabet);

    int hammingDistance(Word w1, Word w2) const;

    Word _generateWordStartingWith(int symbol, int length);

    void print();
private:
    BagOfWords _omegaS;
    BagOfWords _omegaM;
    BagOfWords _omegaL;
    vector<int> _alphabet;

    Word _generateRandomWordOverAlphabet(int length);

    bool _hammingConditionMet(Word word);

    bool _checkHammingCondition(Word word, vector<Word> wordsToCompare);

    void _checkGlobalConditions();
};

#endif //AC_WORDS_GENERATOR_H
