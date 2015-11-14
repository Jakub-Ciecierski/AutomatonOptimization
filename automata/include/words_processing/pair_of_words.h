//
// Created by dybisz on 11/14/15.
//

#ifndef AC_PAIR_OF_WORDS_H
#define AC_PAIR_OF_WORDS_H

#include "word.h"

class PairOfWords {
public:
    PairOfWords();
    PairOfWords(Word word1, Word word2);
    static string pairsToString(vector<PairOfWords> pairs);

    Word word1;
    Word word2;
};

#endif //AC_PAIR_OF_WORDS_H
