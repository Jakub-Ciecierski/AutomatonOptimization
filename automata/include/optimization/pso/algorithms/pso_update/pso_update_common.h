//
// Created by jakub on 12/1/15.
//

#include <entities/particle.h>

#ifndef AC_PSO_UPDATE_H
#define AC_PSO_UPDATE_H

/*
 * This module contains all functionality needed to update particle positions
 */

namespace pso
{
    namespace update
    {
        /*
         * Update all particles
         */
        void updateParticles(std::vector<Particle*>* particles);

        /*
         * Moves particle to given position, with max velocity.
         * In other words, the position that each dimension of particle
         * can change in one iteration is bounded by max velocity
         */
        void moveParticleWithMaxVelocity(Particle* particle,
                                        Point<double>* toPoint);

        /*
         * Bounds the position of the particle within the solution space
         * Each dimension is check, if it is out of interval, set it on the edge
         * and reset the velocity corresponding to that dimension.
         */
        void boundPositionWithInterval(Particle* particle);
    }
}

#endif //AC_PSO_UPDATE_H

