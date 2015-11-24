//
// Created by dybisz on 11/13/15.
//

#ifndef AC_WORDS_GENERATOR_H
#define AC_WORDS_GENERATOR_H

#include <stdexcept>
#include "logger.h"
#include "global_settings.h"
#include "bag_of_words.h"
#include "word.h"
#include "utils.h"
#include "pair_of_words.h"

using namespace global_settings;

class WordsGenerator {
public:
    WordsGenerator(vector<int> alphabet);

    int hammingDistance(Word w1, Word w2) const;

    void _fillBagWithWords(BagOfWords &bag, int numberOfWords);

    vector<PairOfWords>* getPairs();

    void print();

private:
    vector<int> _alphabet;
    BagOfWords _omegaS;
    BagOfWords _omegaM;
    BagOfWords _omegaL;
    vector<PairOfWords> _pairs;

    Word _generateWordStartingWith(int symbol, int length);

    Word _generateRandomWordOverAlphabet(int length);

    bool _hammingConditionMet(Word word);

    bool _checkHammingCondition(Word word, vector<Word> wordsToCompare);

    // To generalize method of calculating minimal hamming distance
    // between consecutively generated words.
    int _calculateAcceptableHammingDistance(int length);

    void _checkGlobalConditions();

    int _generateRandomSymbolFromAlphabet();

    void _fillBags();

    Word _generateWordWithHammingConditionMet(BagOfWords &minWordLength);

    void _generatePairs();

    vector<Word> _collectAllWordsFromBags();

    vector<PairOfWords> _combineIntoPairs(vector<Word> words);

    int _calculatePlotkinForBinaryAlphabet(int n, int d);

    Word _generateWordStartingWith(BagOfWords &bag, int startingSymbol, int wordLength);
};

#endif //AC_WORDS_GENERATOR_H
