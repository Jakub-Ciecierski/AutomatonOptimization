#ifndef AC_MAIN_H
#define AC_MAIN_H

#define LOG_TYPE DEBUG_LOG

#include "error.h"
#include <iostream>
#include <optimizer.h>
#include <dfa_loader.h>
#include <words_gen_experiment.h>
#include "drawer.h"
#include "flag_reader.h"
#include "log.h"
#include "thread_util.h"
#include "dfa_gen_experiment.h"
#include "optimizer_experiment.h"

using namespace std;

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

/*
 * Initialises the application resources
 */
void initApp(int argc, char *argv[]);

/*
 * Closes the application resources
 */
void closeApp();

//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    initApp(argc, argv);

    // Choose experiment
    switch (global_settings::EXPERIMENT_ID){
        case 0:
        experiments::runOptimizerExperiment();
            break;
        case 1:
        experiments::runDFAGenerationExperiment();
            break;
        case 2:
        experiments::runWordsGenerationExperiment();
        break;
        default:
        std::string what = "Experiment ID: " +
                            std::to_string(global_settings::EXPERIMENT_ID) +
                            " is not a proper Experiment ID";
        console::usage(argv[0], what.c_str());
    }

    closeApp();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void initApp(int argc, char *argv[]) {
    // Start the seed
    utils::seed();

    // Read flags must be first!!!!
    console::readFlags(argc, argv);

    // Set the number of threads to be activated
    threading::setTrueNumberOfThreads();

    // Initiates the logging functionality
    logger::initLog();

    // Prints all settings to the console
    global_settings::printSettings();

}

void closeApp(){
    logger::closeLog();
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

#endif //AC_STANDARD_TRANSITION_T_H