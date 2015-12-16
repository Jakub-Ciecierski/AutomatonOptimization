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

/*
 * Class in charge of generating sets of words. It produces both,
 * training and testing sets. Words are generated in two ways:
 * >> All possible upt to some constant _C
 * >> Randomly distributed over some interval of lengths
 *
 * Testing set is completly distinct from training one for better
 * results in measuring precision of the algorithm.
 * What is more it is capable of loading data from and to a fila
 * to save time during testing process. The utility is also usefull when it
 * comes to recreating results or writing reports after tests.
 */
class WordsGenerator {
public:
    // Set of intermediate variables.
    // They contains different sets of generated words.
    vector<Word> _trainingSet;
    vector<Word> _firstSubset;
    vector<Word> _secondSubset;
    vector<Word> _testingSet;

    // Set of variables, which are main aim of the class.
    // _trainingAllSet = _trainingLongSet + _trainingLongSet
    // _trainingShortSet: all words of lengths up to constant _C,
    //                    over some alphabet
    // _trainingLongSet: set of randomly generated words over some
    //                   lengths interval
    // They have been created as a pointers to save space.
    vector<Word*> _trainingAllSet;
    vector<Word*> _trainingShortSet;
    vector<Word*> _trainingLongSet;
    vector<Word*> _testSet;

    // Constructors and destructor part.
    // Three types of constructors have been adapted to user's needs.
    // Alhtough first one is for intermediate test, which we have performm
    // and it should be treated as rather obsolete element of the class,
    // next two are more usefull.
    // Second one generates words having all needed parameters i.e.:
    // >> alphabet wo working on; vector of consecutive integers execeted
    // >> c - costant up to which all possible words are going to be
    //        generated
    // >> trainingSetCount - number of words in training set
    // >> trainingSetMaxLength - maximal length of words in training set,
    //                           > c, which is of course checked.
    // >> testSetCount - number of words in testing set
    // >> testSetMaxLength - maximal length of words in testing set,
    //
    // Thrid one, on the other hand, accepts url to file contatining words.
    // File should be formatted as follows:
    //    #TRAINING SET CONST: 30
    //    #TRAINING SET RAND: 1970
    //    #TESTING SET: 2000

    //    [ALPHABET]
    //    (... integers separated by commas ...)
    //
    //    [TRAINING SET CONST]
    //    (... integers separated by commas ...)
    //
    //    [TESTING SET]
    //    (... integers separated by commas ...)
    //
    WordsGenerator(vector<int> alphabet);
    WordsGenerator(vector<int> alphabet, int c, int trainSetCount,
    int trainSetMaxLength,int testSetCount, int testSetMaxLength);
    WordsGenerator(string url);
    ~WordsGenerator();

    // Auxiliary method for finding hamming distance between two words.
    // It is usefull also outside of the class, hence it have been created
    // as public
    int hammingDistance(Word w1, Word w2) const;

    // Two methods devoted to process of loading and saving words from file.
    // They are public, because user may want to again load or save words in
    // the class, hence it is useful to not generating new object.
    void _saveWordsToFIle();
    void _loadWordsFromFile(string url);

    // After words generation, all of them must be combined into pairs to be
    // tested against fitness function. Those two methods returns words
    // from training and testing sets combined into pair.
    vector<PairOfWords>* getPairs();
    vector<PairOfWords>* getTestPairs();

    // Simple set of getters and setters for appropriate fields
    const vector<Word*>* getTrainingAllSet() const;
    const vector<Word*>* getTrainingShortSet() const;
    const vector<Word*>* getTrainingLongSet() const;
    const vector<Word*>* getTestSet() const;

    // Prints training and testing sets in console
    void print();

private:
    // During flow of the class, these are useful variables, helping not
    // recalculating thing again and again.
    vector<int> _alphabet;
    vector<int>	_pairsTraining;
    vector<int>	_pairsTesting;

    // Few parameters loaded either from file or provded be user.
    int _C;
    int _wordsInTrainingSet;
    int _wordsInFirstSubset;
    int _wordsInSecondSubset;
    int _maxWordLengthTraining;
    int _wordsInTestingSet;
    int _maxWordLengthTesting;

    // Determine signatures of coments and different headers in a file coding
    char _commentSign = '#';
    char _testHeaderSign = '[';

    // All itermediate methods related to creating words of diiferent sizes,
    // starting from different letters, over distinct intervals etc.
    void _calculateNumberOfWords();
    vector<Word> _createAllWordsUpToLength(int N);
    vector<Word> _createRandomWordsOfLengthInInterval(int minLength, int maxLength, int count);
    Word _generateRandomWordOverAlphabet(int length);
    vector<Word> _getWordsOfSizeN(vector<Word> inputSet, int n);
    int _generateRandomSymbolFromAlphabet();

    // Due to exceptions handling methods on different abstract levels ware
    // needed and used.
    void _createAlphabet(int n);
    void _generateWords();
    vector<Word> _initBaseWords();
    void _checkGlobalConditions();
    vector<PairOfWords> _combineIntoPairs(vector<Word> words);
    
    // During file processing, we were loaded its consecutive parts, which
    // sometimes forced us to rewrite soem parts, hence we just encapsulated
    // it by methods.
    void _loadHeader(ifstream & infile);
    vector<Word*> _parseWords(ifstream & infile);

    // Saving laoded/created data to file
    void _printInfo();
};

#endif //AC_WORDS_GENERATOR_H
