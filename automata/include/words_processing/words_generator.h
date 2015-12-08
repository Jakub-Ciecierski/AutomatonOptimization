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
#include <algorithm>   

using namespace global_settings;

class WordsGenerator {
public:

    ///////// NEW SET OF FUNCTIONS /////////////
	vector<Word> _psoWords;
    void  _createAllWordsUpToLength(int N);
	void printAllKLength(vector<int> alphabet, int k);
	void printAllKLengthRec(vector<int> alphabet, Word word, int n, int k);

    WordsGenerator(vector<int> alphabet);

    int hammingDistance(Word w1, Word w2) const;

    void _fillBagWithWords(BagOfWords &bag, int numberOfWords);

    vector<PairOfWords>* getPairs();

    vector<PairOfWords>* getTestPairs();

    void print();

private:
    vector<int> _alphabet;
    BagOfWords _omegaS;
    BagOfWords _omegaM;
    BagOfWords _omegaL;
    BagOfWords _testSet;
    vector<PairOfWords> _pairs;
    vector<PairOfWords> _testPairs;

	
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

    void _generatePairs();

    void _generateTestPairs();

    vector<Word> _collectAllWordsFromBags();

    vector<PairOfWords> _combineIntoPairs(vector<Word> words);

    Word _generateWordStartingWith(BagOfWords &bag, int startingSymbol, int wordLength);

    void _fillTestBag(int numberOfTestWords);
    

};

#endif //AC_WORDS_GENERATOR_H
