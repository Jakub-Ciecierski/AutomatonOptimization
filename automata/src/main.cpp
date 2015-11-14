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
    vector<int> alphabet = {1, 2, 3, 4};
    WordsGenerator wordsGenerator(alphabet);
    Word a = wordsGenerator._generateWordStartingWith(1,5);
    Word b = wordsGenerator._generateWordStartingWith(2,5);
    Word c = wordsGenerator._generateWordStartingWith(4,5);
    cout <<a.toString() + " " + b.toString() + " " + c.toString() + "\n";
    return EXIT_SUCCESS;
}

#endif //AC_STANDARD_TRANSITION_T_H