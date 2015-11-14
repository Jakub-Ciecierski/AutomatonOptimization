//
// Created by dybisz on 11/12/15.
//

#ifndef AC_GLOBAL_SETTINGS_H
#define AC_GLOBAL_SETTINGS_H

#include <string>

// Few remarks about whole project:
// |--o   symbols take values from interval [1; _numberOfSymbols]
// |--o   states are marked by values from interval [1; _numberOfStates]
// |--o   actual values declared in global_settings.cpp (<3 c++)
// |--o   alphabet is represented by integers from interval [_alphabet[0], _alphabet.size()]

namespace global_settings {

    /* ------ PSO SETTINGS ----- */
    // URL to file with tool automaton
    extern std::string TOOL_URL;
    // Minimum states to check
    extern int MIN_STATES;
    // Maximum number of states to check
    extern int MAX_STATES;

    /* ------ WORDS GENERATION ----- */
    // Maximum number of testing words
    extern int R_MAX;
    // Number of words in omega_{S}
    extern int SIZE_S;
    // Number of words in omega_{M}
    extern int SIZE_M;
    // Number of words in omega_{L}
    extern int SIZE_L;
    // Minimum word length in omega_{S}
    extern int MIN_LENG_S;
    // Maximum word length in omega_{S}
    extern int MAX_LENG_S;
    // Minimum word length in omega_{M}
    extern int MIN_LENG_M;
    // Maximum word length in omega_{M}
    extern int MAX_LENG_M;
    // Minimum word length in omega_{L}
    extern int MIN_LENG_L;
    // Maximum word length in omega_{L}
    extern int MAX_LENG_L;

    /* ------ CLUSTERING ----- */
    // The convergence tolerance in kmeans
    extern double KM_TOL;
    // The maximum iterations of kmeans
    extern int KM_MAX_ITER;
}


#endif //AC_GLOBAL_SETTINGS_H
