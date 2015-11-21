#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include <optimizer.h>
#include "utils.h"
#include "global_settings.h"
#include "pso.h"
#include "word.h"
#include "bag_of_words.h"
#include "words_generator.h"
#include "plotkin_bound.h"

using namespace std;

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    if (argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }

    Optimizer opt(argv[1]);
    opt.start();

    PlotkinBound plotkinBound;
//    int res1 = plotkinBound.calculate(2, 2, 1);
//    LOG_CALC("res1", res1);

//    int res2 = plotkinBound.calculate(2, 5, 2);
//    LOG_CALC("res2", res2);
//
//    int res3 = plotkinBound.calculate(2, 4, 4 / 2);
//    LOG_CALC("res3", res3);
//
//    int res4 = plotkinBound.calculate(2 ,6 , 6/2);
//    LOG_CALC("res4", res4);

    return EXIT_SUCCESS;
}

#endif //AC_STANDARD_TRANSITION_T_H