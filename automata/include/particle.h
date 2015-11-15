//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PARTICLE_H
#define AC_PARTICLE_H

#include <vector>
#include <stdexcept>
#include "dfa.h"
#include "math/point.h"
#include "utils.h"
#include "global_settings.h"

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
    Particle(int numberOfStates, int numberOfSymbols, double speedFactor);

    void update();

    ~Particle();

    DFA *_particleRepresentation = NULL;
    Point<double> _position;

    // Position of reaching its personal best fitness value.
    Point<double> pbest;
    // Position of some other particle reaching the best
    // fitness value among all particles within a neighbourhood.
    Point<double> lbest;

    // Best fitness value obtained by itself so far.
    double bestFitness;

private:
    int _length;
    Point<double> _velocity;
    double _maxVelocity;
    double _speedFactor;
    int _numberOfSymbols;
    int _numberOfStates;

    // The maximum change in position that one particle can take
    // during a single iteration.
    double velocity_max;

    // The lower bound of interval
    double intervalMin;
    // The upper bound of interval
    double intervalMax;

    vector<int> _castFromPositionToDFA(Point<double> position);

    void _loadAndLogRandomPosition(int length, double dim, double maxDim);

    string _positionToString();

    Point<double> _generateRandomPosition(int length, double minDim, double maxDim);

    void _loadAndLogDFA(int i, int i1, Point<double> point);

    void _loadAndLogRandomVelocity(double minDim, double maxDim);

    void _loadAndLogMaxVelocity(int numberOfStates, double speedFactor);

    Point<double> _generateRandomPointInSphere(Point<double> centerOfGravity, Point<double> oldPosition);

    void _checkBorderConditions(Point<double>& position);
};

#endif //AC_PARTICLE_H
