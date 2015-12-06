//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PSO_H
#define AC_PSO_H

#include <vector>
#include <string>
#include <stdexcept>
#include <climits>
#include "pso_common.h"
#include "particle.h"
#include "words_generator.h"
#include "console_plot.h"

/*
 * Particle Swarm Optimization.
 *
 * 1) Initialize group of particles - the swarm.
 *
 * 2) For each particle
 *      2.1) Calculate its fitness value, using the fitness function.
 *          Module: pso_fitness.h
 *
 *      2.2) Compare the fitness value to its best obtained so far,
 *          the better value is stored as best_fitness_value.
 *          The position of reaching best_fitness_value is stored in pbest.
 *          Module: pso_fitness.h
 *
 *      2.3) Update neighbourhood and lbest position.
 *          Module: pso_neighbourhood.h
 *
 *       2.4) Update velocity and position.
 *          Module: pso_update
 *
 * 3) Repeat 2) until an ending criterion is met.
 *
 * 4) Output the best solutions. There might be several equaly best solutions,
 *  having the same fitness Value.
 *
 * Note: In the methodology, points 2.3) and 2.4) were swapped. The current
 * positions is the correct one - Inform about that in the final documentation.
 *
 */
class PSO {
public:
    PSO(unsigned int numberOfStates, unsigned int numberOfSymbols,
        vector<int>* toolRelationResults, WordsGenerator* wordsGenerator);

    ~PSO();

    /*
     * Starts computations of PSO
     */
    void compute();

    /*
     * Returns results.
     * There can be many equally good results.
     */
    std::vector<Particle*> getBestParticles();

private:
    unsigned int _numberOfStates;
    unsigned int _numberOfSymbols;
    unsigned int _swarmSize;

    // Used in Fitness Function in order to retrieve pairs of words
    WordsGenerator *_wordsGenerator;
    // Used in Fitness function in order to compare results of each
    // particle to tool results.
    vector<int>* _toolRelationResults;

    // The particles vector
    vector<Particle *> _particles;
    // Position corresponding to the particles.
    // Used in neighbourhood update
    // in order to avoid lazy retrieval of these points
    vector<const Point<double>*> _particlePositions;

    // Best fitness value overall.
    // Global best with regards to all particles
    double _globalBestFitness;

    // The best particles thus far.
    // Recall that it might happen that some particles are equally good
    // in terms of fitness value.
    //
    // The current values to take are pbest and bestFitnessValue
    // NOT the current position !!!
    std::vector<Particle*> _bestParticles;

    int _lastNumberOfClusters;

    // Measures time of computations of each step
    pso::TimeMeasures timeMeasures{0,0,0};

    ParticleDecoder* _particleDecoder;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    void _initFitnessFunctionParallel();

    /*
     * Loads swarm size based on the parameters
     */
    void _loadSwarmSize();

    /*
     * Generates Particles based on the parameters
     */
    void _generateParticles();

    /*
     * Checks whether PSO should stop.
     * The ending criteria is based on maximum number of iterations
     * and the FITNESS_TOLERANCE value.
     *
     * @t - the iteration number
     */
    bool _isConverged(const int &t);

    void _printInfoAndPlot(int t, ConsolePlot *cPlot,
                           int &totalNumberOfLinesToReset);
};

#endif //AC_PSO_H
