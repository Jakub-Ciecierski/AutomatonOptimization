//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PARTICLE_H
#define AC_PARTICLE_H

#include "dfa.h"
#include "point.h"

class Particle {
private:
    Point<double> _position;
    DFA _particleRepresentation;
};

#endif //AC_PARTICLE_H
