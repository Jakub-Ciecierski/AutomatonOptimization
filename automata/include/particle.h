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

class Particle {
public:
    Particle(int numberOfStates, int numberOfSymbols, double speedFactor);

    void update(Point<double> pbestp, Point<double> lbestp);

    ~Particle();

    DFA *_particleRepresentation = NULL;
    Point<double> _position;

private:
    int _length;
    Point<double> _velocity;
    double _maxVelocity;
    double _speedFactor;
    int _numberOfSymbols;
    int _numberOfStates;

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
