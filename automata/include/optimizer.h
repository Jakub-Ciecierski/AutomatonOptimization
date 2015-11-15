//
// Created by jakub on 11/15/15.
//

#ifndef AC_OPTIMIZER_H
#define AC_OPTIMIZER_H


#include "pso.h"

/*
 * The Stochastic Algorithm for Deterministic Finite Automaton Optimization.
 *
 * Given is a tool that is able to answer whether two given
 * words over the alphabet are in relation R-L induced by the language L or not.
 * In this case the tool is some DFA T.
 *
 * The algorithm tries to find an optimal DFA accepting the language L.
 *
 * 1) Select a sample set of words Omega.
 *
 * 2) Using the tool T, compute the the relation R-L for the given set of words.
 *  Store the results.
 *
 * 3) Run PSO for { (n_min), (n_min +1) ,... , (n_max) } number of states.
 *  For each such PSO instance - The following should be done inside PSO:
 *      3.1) After each iteration of PSO,
 *          encode each particle p to automaton A_p.
 *      3.2) Compute the relation R-L for each A_p.
 *      3.3) Compare the results with T.
 *      3.4) After PSO converges, save the best result - the most optimal DFA
 *
 * 4) Choose the best result among all PSO instances.
 *  Note: It may happen that two automata have the same result (very unlikely).
 *  Then the automaton that uses the least amount of states to compute the words
 *  from set Omega will be chosen.
 *
 */
class Optimizer {

    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // The PSO instances
    PSO* pso;

    // The DFA tool used to compute R-L.
    DFA* tool;

    // Generates the sample set of words Omega
    WordsGenerator* _wordsGenerator;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * 1) Select a sample set of words Omega
     */
    void generateWords();

    /*
     * 2) Compute the relation R-L of the given set of words Omega for the
     * DFA tool T.
     *
     * The result is saved in TODO.
     */
    void computeRelation();

    /*
     * 3) Runs PSO instances.
     */
    void runPSO();

    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    Optimizer();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts the computations.
     */
    void start();

};


#endif //AC_OPTIMIZER_H
