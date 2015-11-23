#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include <optimizer.h>
#include "flag_reader.h"
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
void initApp(int argc, char *argv[]);

/*
 * Closes the application resources
 */
void closeApp();

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    initApp(argc, argv);

    Optimizer opt(global_settings::TOOL_URL);
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

void initApp(int argc, char *argv[]) {
    // Read flags must be first!!!!
    console::readFlags(argc, argv);

    logger::initLog();


}
void closeApp(){
    logger::closeLog();
}

#endif //AC_STANDARD_TRANSITION_T_H