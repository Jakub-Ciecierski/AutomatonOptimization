//
// Created by jakub on 11/15/15.
//

#ifndef AC_OPTIMIZER_H
#define AC_OPTIMIZER_H

#include "pso.h"
#include "log.h"

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
 *      4.1) If PSO instance returns many results, choose the one
 *          using minimum amount of states.
 *          Otherwise simply choose the only one.
 *      4.2) Compare the best solution from 4.1) with the best so far.
 *          The one with better fitness value is new best.
 *      4.3) Finish if the fitness tolerance has been matched
 *
 *  To summarise Point 4): First we choose the best fitness value, then
 *  among equally good, the ones with minimum states.
 *
 *  Note: It may happen that two automata have the same result (very unlikely).
 *  Then the automaton that uses the least amount of states to compute the words
 *  from set Omega will be chosen.
 *
 */
class Optimizer {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // The PSO instances
    PSO* pso;

    // The DFA tool used to compute R-L.
    DFA* tool;

    // Generates the sample set of words Omega
    WordsGenerator* _wordsGenerator;

    vector<int> _toolRelationResults;

    Particle* bestParticle;
    double bestTestingSetResult;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Select a sample set of words Omega
     */
    void generateWords();

    /*
     * Compute the relation R-L of the given set of words Omega for the
     * DFA tool T.
     *
     * The result is saved in _toolRelationResults.
     */
    void computeRelation();

    /*
     * Computes error of given particle and word set
     */
    double computeError(Particle* particle, const std::vector<Word*>* set);

    /*
     * Runs PSO instances.
     *
     * @s - number of states
     * @r - number of symbols in alphabet.
     */
    void runPSOLogic(int s, int r);

    /*
     * Selects the best result.
     * The best DFA is the one that uses the least amount of states
     * to compute all words
     */
    Particle* selectParticleUsingMinimumStates(
            const std::vector<Particle *>& results);

    /*
     * Compares the result with current bestResult
     * The better one is saved.
     */
    void compareResultWithBestResult(Particle* result,
                                     double testSetResult);

    void summarize(Particle* particle, int psoStateCount,
                              double testSetResult,
                              double trainingShortResult,
                              double trainingLongResult,
                              double trainingAllResult,
                              std::string headerInfo);

    void summarizeBestPSOResult();

    void summarizeTool(DFA* tool);

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    Optimizer(DFA * tool);

    ~Optimizer();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts the computations.
     */
    void start();

    const Particle* getBestParticle() const;

    const DFA* getTool() const;
};


#endif //AC_OPTIMIZER_H
