//
// Created by dybisz on 11/12/15.
//

#ifndef AC_GLOBAL_SETTINGS_H
#define AC_GLOBAL_SETTINGS_H

#include <string>
#include <cmath>

// Few remarks about whole project:
// |--o   symbols take values from interval [1; _numberOfSymbols]
// |--o   states are marked by values from interval [1; _numberOfStates]
// |--o   actual values declared in global_settings.cpp (<3 c++)
// |--o   alphabet is represented by integers from interval [_alphabet[0], _alphabet.size()]

namespace global_settings {
    /* ------ EXPERIMENT SETTINGS----- */
    // ID of experiment to run
    // 0: Main optimizer
    // 1: DFA Generation
    extern int EXPERIMENT_ID;

    /* ------ Words GENERATION SETTINGS ----- */
    extern int GEN_WORDS_SYMBOL_COUNT;
    extern int GEN_WORD_C;
    extern int GEN_WORD_TRAIN_COUNT;
    extern int GEN_WORD_TRAIN_MAX_LENGTH;
    extern int GEN_WORD_TEST_COUNT;
    extern int GEN_WORD_TEST_MAX_LENGTH;

    /* ------ DFA GENERATION SETTINGS ----- */
    extern std::string GEN_DFA_PATH;
    extern int GEN_DFA_STATES;
    extern int GEN_DFA_SYMBOLS;

    /* ------ OPTIMIZER SETTINGS ----- */
    // Minimum states to check
    extern int MIN_STATES;
    // Maximum number of states to check
    extern int MAX_STATES;

    /* ------ PSO SETTINGS ----- */
    // URL to file with tool automaton
    extern std::string TOOL_URL;
    extern std::string WORDS_PATH;
    // Maximum iterations of PSO algorithm
    extern int MAX_ITER;
    // TODO comment
    extern double LEARNING_FACTOR;
    // TODO comment
    extern double PARTICLE_VEL_WEIGHT;

    // When encoding particle back to automaton
    // each dimension must be casted down to integer value.
    // If p[i] > x.5 then take the ceiling.
    // otherwise take the floor.
    // Formally:
    //      encodedValue = (int)p[i]
    //      delta = p[i] - encodedValue
    //      if delta > ENCODING_DELTA
    //          encodedValue++
    //
    extern double ENCODING_DELTA;

    // Becouse of the nature of the encoding the
    // upper interval bound must a bit less than:
    // n + ENCODING_DELTA
    extern double UPPER_BOUND_ERR;

    // The factor of the maximum change in position that one particle can take
    // during a single PSO iteration.
    extern double SPEED_FACTOR;

    // The maximum change that particle can make in single iteration
    extern double MAX_VELOCITY;

    // The swarm size is scaled by this factor
    extern double POPULATION_FACTOR;

    // Look for fitness value no bigger than FITNESS_TOLERANCE
    // Possible values: [0, 1], where 1 is the most optimal DFA.
    extern double FITNESS_TOLERANCE;
    extern int SWARM_SIZE;

    /* ------ THREAD SETTINGS ----- */

    // If the optimal number of threads can not be determined by the system
    // this value will be used
    extern int DEFAULT_THREAD_COUNT;

    // The actual number of threads to be used in computation.
    // If the value is below 1, then it will be up to the system to choose
    // the optimal number of threads.
    // If the optimal number of threads can not be determined, then
    // DEFAULT_THREAD_COUNT will be used.
    extern int TRUE_THREAD_COUNT;

    /* ------ CLUSTERING ----- */
    // The convergence tolerance in kmeans
    extern double KM_TOL;
    // The maximum iterations of kmeans
    extern int KM_MAX_ITER;

    // Starting number of cluster to evaluate.
    extern int START_K;
    // Finishing number of cluster to evaluate.
    extern int END_K;


    /* ------ LOGGER ----- */
    // Main directory of logs
    extern std::string LOG_MAIN_DIR;

    // Directory of current computation instance
    extern std::string LOG_CURR_DIR;

//------------------------------------------------------------------------------

    /*
     * Prints all the settings.
     * TODO Do it automatically.
     */
    void printSettings();
}


#endif //AC_GLOBAL_SETTINGS_H
