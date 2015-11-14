//
// Created by dybisz on 11/14/15.
//

#include "pair_of_words.h"

PairOfWords::PairOfWords() { }

PairOfWords::PairOfWords(Word word1, Word word2) : word1(word1), word2(word2) { }

string PairOfWords::pairsToString(vector<PairOfWords> pairs) {
    std::string stringOut = "";

    for (auto i = pairs.begin(); i != pairs.end(); ++i) {
        stringOut += "(" + (*i).word1.toString() + ", " + (*i).word2.toString() + ")\n";
    }

    return stringOut;
}

