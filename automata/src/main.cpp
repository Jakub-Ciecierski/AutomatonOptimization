#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include <optimizer.h>
#include "log.h"
#include "utils.h"
#include "global_settings.h"
#include "pso.h"
#include "word.h"
#include "bag_of_words.h"
#include "words_generator.h"
#include "plotkin_bound.h"
#include "random_sphere.h"
#include "point.h"

using namespace std;

/*
 * Initialises the application resources
 */
void initApp();
/*
 * Closes the application resources
 */
void closeApp();

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    if (argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }

    initApp();

    Optimizer opt(argv[1]);
    opt.start();

    closeApp();

//    Point<double> G;
//    G.addDimension(4.0);
//    G.addDimension(6.0);
//    G.addDimension(1.0);
//    G.addDimension(2.0);
//    G.addDimension(3.0);
//    G.addDimension(4.0);
//
//    Point<double> X_p;
//    X_p.addDimension(6.0);
//    X_p.addDimension(4.0);
//
//    RandomSphere rs(G, X_p);
//    cout << "SPHERE GENERATED: " << rs.toString() << endl;
//
//    for(int i = 0; i < 5 ; i++) {
//        Point<double> temp = rs.generatePointWithin();
//        cout << "Generated point: " << temp.toString() << endl;
//    }

    return EXIT_SUCCESS;
}

void initApp() {
    logger::initLog();
}
void closeApp(){
    logger::closeLog();
}

#endif //AC_STANDARD_TRANSITION_T_H