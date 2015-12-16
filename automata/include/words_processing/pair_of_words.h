//
// Created by dybisz on 11/14/15.
//

#ifndef AC_PAIR_OF_WORDS_H
#define AC_PAIR_OF_WORDS_H

#include "word.h"

/*
 * Basic data strcture encapsulating two words. It prevents application
 * from creating another 'naked' vector. Instead, one can easily pack up
 * two words and manage them.
 */
class PairOfWords {
public:
    // User can either create empty pari and later add words, or start
    // with some declared ones.
    PairOfWords();
    PairOfWords(Word word1, Word word2);

    // Convert the pair into string. Usefull in the debuggin process
    static string pairsToString(vector<PairOfWords> pairs);

    // Words are public, because it is rather data structur than a class.
    Word word1;
    Word word2;
};

#endif //AC_PAIR_OF_WORDS_H
