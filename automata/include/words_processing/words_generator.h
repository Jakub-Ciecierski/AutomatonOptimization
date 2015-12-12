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
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace global_settings;

class WordsGenerator {
public:
    vector<Word> _trainingSet;
    vector<Word> _firstSubset;
    vector<Word> _secondSubset;
    vector<Word> _testingSet;

    vector<Word*> _trainingAllSet;
    vector<Word*> _trainingShortSet;
    vector<Word*> _trainingLongSet;
    vector<Word*> _testSet;

    WordsGenerator(vector<int> alphabet);
    WordsGenerator(vector<int> alphabet,
               int c, int trainSetCount,
               int trainSetMaxLength,
               int testSetCount,
               int testSetMaxLength);
    // URL to file; training and testing sets are loaded
    WordsGenerator(string url);
    ~WordsGenerator();

    int hammingDistance(Word w1, Word w2) const;
    void _saveWordsToFIle();
    void _loadWordsFromFile(string url);
    vector<PairOfWords>* getPairs();
    vector<PairOfWords>* getTestPairs();

    const vector<Word*>* getTrainingAllSet() const;
    const vector<Word*>* getTrainingShortSet() const;
    const vector<Word*>* getTrainingLongSet() const;
    const vector<Word*>* getTestSet() const;

		void print();

private:
    vector<int> _alphabet;

		vector<int>	_pairsTraining;
		vector<int>	_pairsTesting;

		void _calculateNumberOfWords();
		vector<Word> _createAllWordsUpToLength(int N);
		vector<Word> _createRandomWordsOfLengthInInterval(int minLength, int maxLength, int count);
		void _createAlphabet(int n);
		vector<Word> _initBaseWords();
		vector<Word> _getWordsOfSizeN(vector<Word> inputSet, int n);

		int _C;
		int _wordsInTrainingSet;
		int _wordsInFirstSubset;
		int _wordsInSecondSubset;
		int _wordsInTestingSet;
		int _maxWordLengthTraining;
		int _maxWordLengthTesting;
		char _commentSign = '#';
		char _testHeaderSign = '[';

		// GENERATING WORDS
    Word _generateRandomWordOverAlphabet(int length);
    void _checkGlobalConditions();
		void _loadHeader(ifstream & infile);
    int _generateRandomSymbolFromAlphabet();
		void _printInfo();
		vector<Word*> _parseWords(ifstream & infile);

    vector<PairOfWords> _combineIntoPairs(vector<Word> words);
    void _generateWords();


};

#endif //AC_WORDS_GENERATOR_H
