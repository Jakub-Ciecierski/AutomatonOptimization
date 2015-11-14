//
// Created by dybisz on 11/13/15.
//

#include "words_generator.h"

WordsGenerator::WordsGenerator(vector<int> alphabet) : _alphabet(alphabet) {
    try {
        utils::seed();
        _checkGlobalConditions();
        _fillBags();
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
}

// Conditions specified in methodology
void WordsGenerator::_checkGlobalConditions() {

    if (SIZE_S + SIZE_M + SIZE_L > R_MAX) {
        throw invalid_argument("omega_s + omega_m + omega_l > r_max; check your flags.");
    }

    if (MAX_LENG_S >= MIN_LENG_M) {
        throw invalid_argument("MAX_LENG_S > MIN_LENG_M; words from omega_S might be longer than those in omega_M");
    }

    if (MAX_LENG_M >= MIN_LENG_L) {
        throw invalid_argument("MAX_LENG_M > MIN_LENG_L; words from omega_M might be longer than those in omega_L");
    }
}

void WordsGenerator::_fillBags() {
    _fillBagWithWords(_omegaS, SIZE_S, MIN_LENG_S, MAX_LENG_S);
    _fillBagWithWords(_omegaM, SIZE_M, MIN_LENG_M, MAX_LENG_M);
    _fillBagWithWords(_omegaL, SIZE_L, MIN_LENG_L, MAX_LENG_L);
}

void WordsGenerator::_fillBagWithWords(BagOfWords &bag, int numberOfWords, int minWordLength, int maxWordLength) {
    bool moreWordsNeededThanSymbolsInAlphabet = numberOfWords > _alphabet.size();

    if (moreWordsNeededThanSymbolsInAlphabet) {

        // Create alphabet based words
        for (int symbol = 1; symbol < _alphabet.size(); symbol++) {
            int length = utils::generateRandomNumber(minWordLength, maxWordLength);
            Word word = _generateWordStartingWith(symbol, length);
            bag.addWord(word);
        }

        // Fill up rest of the space
        int restOfTheSpaceSize = numberOfWords - _alphabet.size();
        for (int i = 0; i < restOfTheSpaceSize; i++) {
            Word word = _generateWordWithHammingConditionMet(minWordLength, maxWordLength);
            bag.addWord(word);
        }

    } else {

        // Produce as many alphabet words as words needed
        for (int symbol = 1; symbol < numberOfWords; symbol++) {
            int length = utils::generateRandomNumber(minWordLength, maxWordLength);
            Word word = _generateWordStartingWith(symbol, length);
            bag.addWord(word);
        }
    }
}

int WordsGenerator::hammingDistance(Word w1, Word w2) const {
    int distance = 0;

    if (w1.length() != w2.length()) {
        throw invalid_argument("words have different lengths!");
    }

    for (int i = 0; i < w1.length(); i++) {
        if (w1[i] != w2[i]) {
            distance++;
        }
    }

    return distance;
}

Word WordsGenerator::_generateWordStartingWith(int startingSymbol, int wordLength) {
    Word word;
    do {
        word = _generateRandomWordOverAlphabet(wordLength);
        word[0] = startingSymbol;
    } while (!_hammingConditionMet(word));

    return word;
}

Word WordsGenerator::_generateWordWithHammingConditionMet(int minWordLength, int maxWordLength) {
    Word word;
    do {
        int length = utils::generateRandomNumber(minWordLength, maxWordLength);
        word = _generateRandomWordOverAlphabet(length);
    } while (!_hammingConditionMet(word));

    return word;
}

Word WordsGenerator::_generateRandomWordOverAlphabet(int length) {
    Word word;

    for (int i = 0; i < length; i++) {
        int randomSymbol = _generateRandomSymbolFromAlphabet();
        word.appendSymbol(randomSymbol);
    }

    return word;
}

int WordsGenerator::_generateRandomSymbolFromAlphabet() {
    int firstSymbol = _alphabet[0];
    int lastSymbol = _alphabet.size();
    return utils::generateRandomNumber(firstSymbol, lastSymbol);
}

// Check if word meets conditions regarding those already created
bool WordsGenerator::_hammingConditionMet(Word word) {
    vector<Word> wordsInOmegaS = _omegaS.getWordsOfLength(word.length());
    vector<Word> wordsInOmegaM = _omegaS.getWordsOfLength(word.length());
    vector<Word> wordsInOmegaL = _omegaS.getWordsOfLength(word.length());

    // && ish short-circuit - if first element is false, there is
    // no need for extra calculations
    return _checkHammingCondition(word, wordsInOmegaS) &&
           _checkHammingCondition(word, wordsInOmegaM) &&
           _checkHammingCondition(word, wordsInOmegaL);
}

bool WordsGenerator::_checkHammingCondition(Word word, vector<Word> wordsToCompare) {

    double acceptableHammingDistance = ((double) word.length()) / 2.0;

    for (auto i = wordsToCompare.begin(); i != wordsToCompare.end(); ++i) {
        int distance = hammingDistance(word, *i);

        if (distance < acceptableHammingDistance) {
            LOG_DEBUG("word: " + word.toString() + " and " + (*i).toString()
                      + " have wrong hamming distance: " + to_string(distance));
            print();
            return false;
        }
    }

    return true;
}

void WordsGenerator::print() {
    cout << "OMEG_S:\n";
    _omegaS.print();
    cout << "OMEG_M:\n";
    _omegaM.print();
    cout << "OMEG_L:\n";
    _omegaL.print();
}


