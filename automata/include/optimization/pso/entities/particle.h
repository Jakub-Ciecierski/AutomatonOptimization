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

#include <particle_decoder.h>

class ParticleDecoder;

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
 *
 */
class Particle {
private:
    // DFA Representation of current position
    DFA * _currentDFA = NULL;
    // DFA Representation of best position
    DFA * _pbestDFA = NULL;

    // Current position
    Point<double> _position;

    // current velocity
    Point<double> _velocity;

    // The maximum change in position that one particle can take
    // during a single iteration.
    double _maxVelocity;

    // Position of reaching its personal best fitness value.
    Point<double> _pbest;
    // Position of some other particle reaching the best
    // fitness value among all particles within a neighbourhood.
    Point<double> _lbest;

    // Current Fitness value;
    double _fitness;

    // Best fitness value obtained by itself so far.
    double _bestFitness;

    // The lower bound of interval
    double _intervalMin;
    // The upper bound of interval
    double _intervalMax;

    // Used to decode particle into the object
    ParticleDecoder* _pDecoder;

public:
    Point<double> oldPosition;

    Particle(Point<double> position, Point<double> velocity,
                    double intervalMin, double intervalMax,
                    double maxVelocity, ParticleDecoder* pDecoder);

    Particle(const Particle& p);

    ~Particle();

    /*
     * Updates the DFA representation of the particle
     */
    void updateCurrentDFA();

    /*
     * Save current Configuration as Best result.
     * Saves: pbest, bestFitness, bestDFA.
     */
    void saveCurrentConfigAsBest();

    //-----------------------------------------------------------//
    //  GETTERS
    //-----------------------------------------------------------//

    const DFA * getCurrentDFA() const;

    /*
     * Returns the DFA corresponding to pbest
     */
    const DFA * getBestDFA() const;

    const double& getFitness() const;

    /*
     * Returns best fitness so far
     */
    const double& getBestFitness() const;

    const Point<double>* getPosition() const;
    const Point<double>* getVelocity() const;

    const double& getMaxVelocity() const;

    const Point<double>* getPBest() const;
    const Point<double>* getLBest() const;

    const double& getIntervalMin() const;
    const double& getIntervalMax() const;

    //-----------------------------------------------------------//
    //  SETTERS
    //-----------------------------------------------------------//

    void setFitness(double fitness);

    void setPosition(Point<double> pos);

    /*
     * Set value of dim-th dimension of position vector
     */
    void setPositionDim(double value, int dim);

    void setVelocity(Point<double> vel);

    /*
     * Set value of dim-th dimension of velocity vector
     */
    void setVelocityDim(double value, int dim);

    void setLBest(Point<double> lbest);
};

#endif //AC_PARTICLE_H
