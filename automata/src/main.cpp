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
    PSO pso(argv[1], 6, 2);
    pso.compute();

    return EXIT_SUCCESS;
}

#endif //AC_STANDARD_TRANSITION_T_H