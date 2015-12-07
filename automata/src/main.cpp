#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include "error.h"
#include <iostream>
#include <optimizer.h>
#include <dfa_loader.h>
#include "drawer.h"
#include "flag_reader.h"
#include "log.h"
#include "thread_util.h"

using namespace std;

/*
 * Initialises the application resources
 */
void initApp(int argc, char *argv[]);

/*
 * Closes the application resources
 */
void closeApp();

void summarize(Optimizer &opt);

//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    initApp(argc, argv);

    logger::log("Main Computations Begin");

    logger::log("Loading Tool DFA from file: ", global_settings::TOOL_URL);
    DFA dfaTool = dfa_loader::loadDFA(global_settings::TOOL_URL);

    logger::log("Starting Optimizer");
    // Start Optimizer
    Optimizer opt(&dfaTool);
    opt.start();
    logger::log("Optimizer Finished");

    // Print summary
    summarize(opt);

    logger::log("After print");

    closeApp();

    logger::log("Main Computations End");

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

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


void summarize(Optimizer &opt){

    const Particle* result = opt.getBestParticle();

    const DFA * dfa = result->getBestDFA();

    // Build string for result
    stringstream ss;
    ss << "Result Summary" << std::endl;

    ss << *dfa;
    ss << "Fitness: " << result->getBestFitness();

    drawing::drawDFA(*dfa, "dfa_result");

    stringstream ssTool;
    const DFA * tool = opt.getTool();

    ssTool << "Tool Summary" << std::endl;
    ssTool << *tool;

    drawing::drawDFA(*tool, "dfa_tool");

    logger::log(File("result.txt"), ss.str());
    logger::log(File("result.txt"), ssTool.str());
}


//------------------------------------------------------------------------------

#endif //AC_STANDARD_TRANSITION_T_H