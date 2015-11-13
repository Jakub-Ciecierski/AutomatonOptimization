#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include "utils.h"
#include "global_settings.h"
#include "pso.h"
#include "word.h"
#include "bag_of_words.h"
#include "words_generator.h"

using namespace std;

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    if (argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }
//    PSO pso(argv[1], 5, 1);
    WordsGenerator wg;

    Word w1({1,1,1,0});
    Word w2({1,0,0});

    cout << wg.hammingDistance(w1,w2);
    return EXIT_SUCCESS;
}

#endif //AC_STANDARD_TRANSITION_T_H