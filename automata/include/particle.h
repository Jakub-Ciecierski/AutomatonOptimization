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

class Particle {
public:
    Particle(int numberOfStates, int numberOfSymbols, double speedFactor);

    ~Particle();

private:
    int _length;
    double _velocity;
    double _maxVelocity;
    double _speedFactor;
    Point<double> _position;
    DFA *_particleRepresentation = NULL;

    vector<int> _castFromPositionToDFA(Point<double> position);

    void _loadAndLogRandomPosition(int length, double dim, double maxDim);

    string _positionToString();

    Point<double> _generateRandomPosition(int length, double minDim, double maxDim);

    void _loadAndLogDFA(int i, int i1, Point<double> point);

    void _loadAndLogRandomVelocity(double minDim, double maxDim);

    void _loadAndLogMaxVelocity(int numberOfStates, double speedFactor);
};

#endif //AC_PARTICLE_H
