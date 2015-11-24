#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE DEBUG_LOG

#include <iostream>
#include <optimizer.h>
#include "flag_reader.h"
#include "log.h"

using namespace std;

/*
 * Initialises the application resources
 */
void initApp(int argc, char *argv[]);

/*
 * Closes the application resources
 */
void closeApp();

void printSummary(Optimizer& opt);

//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    initApp(argc, argv);

    logger::log("Main Computations Begin");

    // Start Optimizer
    Optimizer opt(global_settings::TOOL_URL);
    opt.start();

    // Print summary
    printSummary(opt);

    closeApp();

    logger::log("Main Computations End");

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------

void initApp(int argc, char *argv[]) {
    // Read flags must be first!!!!
    console::readFlags(argc, argv);

    logger::initLog();

    global_settings::printSettings();

}
void closeApp(){
    logger::closeLog();
}

void printSummary(Optimizer& opt){

    Particle* result = opt.getResult();

    // Result pack containing DFA of the particle
    ResultPack resultPack = result->getResultPack();
    CodedTransitionTable transitionTableResult =
            resultPack.dfa->getCodedTransitionTable();
    std::vector<int> transVecResult =
            transitionTableResult.getCodedTransitionTable();
    // Build string for result
    stringstream ss;
    ss << "Result Summary" << std::endl;
    ss << "States: ................. "
    << result->_numberOfStates << std::endl;
    ss << "Symbols: ................ "
    << result->_numberOfSymbols << std::endl;
    ss << "Natural Coding: ......... "
    << "[" << utils::vectorToString(transVecResult) << "]" << std::endl;
    ss << "Fitness: ................ "
    << result->bestFitness;

    stringstream ssTool;
    DFA* tool = opt.getTool();
    CodedTransitionTable transitionTable = tool->getCodedTransitionTable();
    std::vector<int> transVec =
            transitionTable.getCodedTransitionTable();
    int symbols = tool->alphabet.size();
    int states = transVec.size() / symbols;
    ssTool << "Tool Summary" << std::endl;
    ssTool << "States: ................. "
        << states  << std::endl;
    ssTool << "Symbols: ................ "
        << symbols << std::endl;
    ssTool << "Natural Coding: ......... "
        << "[" << utils::vectorToString(transVec) << "]";

    logger::log(File("result.txt"), ss.str());
    logger::log(File("result.txt"), ssTool.str());
}
//------------------------------------------------------------------------------

#endif //AC_STANDARD_TRANSITION_T_H