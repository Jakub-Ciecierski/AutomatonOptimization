//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PARTICLE_H
#define AC_PARTICLE_H

#include <vector>
#include <stdexcept>
#include "dfa.h"
#include "point.h"
#include "utils.h"
#include "global_settings.h"

/*
 * Result pack
 */
struct ResultPack{
    DFA* dfa;
    double* fitness;
    Point<double>* position;
};

/*
 * Particle is used to travel through the solution space in PSO algorithm.
 *
 * Each particle contains:
 *      1) Best fitness value obtained by itself so far.
 *          Fitness value represents the quality of the solution.
 *          Fitness value is computed by Fitness function by PSO.
 *
 *      2.1) Current Velocity.
 *      2.2) Current Position.
 *
 *      3.1) pbest - Position of reaching its personal best fitness value.
 *          (pbest stands for previous best, or personal best.)
 *      3.2) lbest - Position of some other particle reaching the best
 *          fitness value among all particles within a neighbourhood.
 */
class Particle {
public:
    DFA *_particleRepresentation = NULL;
    Point<double> _position;

    // Position of reaching its personal best fitness value.
    Point<double> pbest;
    // Position of some other particle reaching the best
    // fitness value among all particles within a neighbourhood.
    Point<double> lbest;

    Point<double> _velocity;

    // Best fitness value obtained by itself so far.
    double bestFitness;

    // Current Fitness value;
    double fitness;

    int _numberOfSymbols;
    int _numberOfStates;

    // The maximum change in position that one particle can take
    // during a single iteration.
    double _maxVelocity;

    // The lower bound of interval
    double _intervalMin;
    // The upper bound of interval
    double _intervalMax;

    Particle(int numberOfStates, int numberOfSymbols);

    Particle(const Particle& p);

    ~Particle();

    /*
     * Updates the DFA that represents this particle.
     */
    void updateDFARepresentation();

    vector<int> _castFromPositionToDFA(Point<double> position);

    ResultPack getResultPack();

private:
    int _length;

    // Result pack for final evaluation
    ResultPack resultPack{NULL, NULL, NULL};

    void _loadAndLogRandomPosition(int length, double dim, double maxDim);

    string _positionToString();

    Point<double> _generateRandomPosition(int length, double minDim, double maxDim);

    void _loadAndLogDFA(int i, int i1, Point<double> point);

    void _loadAndLogRandomVelocity(double minDim, double maxDim);

    void _loadAndLogMaxVelocity(int numberOfStates);

    void _loadInterval();
};

#endif //AC_PARTICLE_H
