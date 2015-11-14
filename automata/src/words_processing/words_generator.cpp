//
// Created by dybisz on 11/13/15.
//

#include "words_generator.h"

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

bool WordsGenerator::_hammingCondition(Word word, int wordLength) {
    vector<Word> wordsToConsider = _getGeneratedWordsOfLength(wordLength);
    // TODO(dybisz)
}

// TODO(dybisz)
vector<Word> WordsGenerator::_getGeneratedWordsOfLength(int length) {
    vector<Word> wordsInOmegaS = _omegaS.getWordsOfLength(length);
    vector<Word> wordsInOmegaM = _omegaS.getWordsOfLength(length);
    vector<Word> wordsInOmegaL = _omegaS.getWordsOfLength(length);
    return _mergeVectors(wordsInOmegaS, wordsInOmegaM, wordsInOmegaS);
}

vector<Word> WordsGenerator::_mergeVectors(vector<Word> v1, vector<Word> v2, vector<Word> v3) {
    // TODO(dybisz)
    return std::vector<Word>();
}
