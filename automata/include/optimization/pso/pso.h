//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PSO_H
#define AC_PSO_H

#include <vector>
#include <string>
#include <stdexcept>
#include <climits>
#include "dfa.h"
#include "particle.h"
#include "words_generator.h"

/*
 * Particle Swarm Optimization.
 *
 * 1) Initialize group of particles - the swarm.
 *
 * 2) For each particle
 *      2.1) Calculate its fitness value, using the fitness function.
 *
 *      2.2) Compare the fitness value to its best obtained so far,
 *          the better value is stored as best_fitness_value.
 *          The position of reaching best_fitness_value is stored in pbest.
 *
 *      2.3) Update neighbourhood and lbest position.
 *
*       2.4) Update velocity and position.
 *
 * 3) Repeat 2) until an ending criterion is met.
 *
 * 4) Output the best solution.
 *
 * Note: In the methodology, points 2.3) and 2.4) were swapped. The current
 * positions is the correct one - Inform about that in the final documentation.
 *
 */
class PSO {
public:
    PSO(int numberOfStates, int numberOfSymbols,
        vector<int>* toolRelationResults, WordsGenerator* wordsGenerator);

    ~PSO();

    void compute();

private:
    vector<Particle *> _particles;
    WordsGenerator *_wordsGenerator;

    // Pointer to best particle within the whole PSO space.
    Particle* bestParticle;
    // Best fitness value overall, global best
    double _globalBestFitness;

    int _psoNumberOfStates;
    int _numberOfSymbols;
    int _swarmSize;

    vector<int>* _toolRelationResults;

    void _loadAndLogSwarmSize();

    int _calculateSwarmSize(int numberOfStates, int numberOfSymbols);

    void _loadAndLogRandomParticles(int numberOfParticles);

    vector<Particle *> _generateRandomParticles(int numberOfParticles);

    double _fitnessFunction(Particle* p);

    void _calculatePBestAndFitness(vector<Particle *> particles);

    void _updateParticles();

    /*
     * Checks whether PSO should stop.
     * The ending criteria is based on maximum number of iterations
     * and the FITNESS_TOLERANCE value.
     *
     * @t - the iteration number
     */
    bool isConverged(const int &t);

    /*
     * Updates the state of neighbourhoods.
     * The data set in the form of all particles
     * are subjected to cluster analysis.
     *
     * 1) Find the optimal number of clusters k.
     * 2) Compute kmeans for that k.
     * 3) Each cluster is a single neighbourhood.
     *
     */
    void _updateNeighbourhoods();

    /*
     * Returns vector of points corresponding to the vector of particles
     *
     * @_particles - The vector of particles to get points from
     */
    vector<Point<double>*> _particlesToPoints(vector<Particle*> _particles);
};

#endif //AC_PSO_H