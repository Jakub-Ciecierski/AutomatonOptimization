//
// Created by jakub on 12/1/15.
//

#ifndef AC_PSO_UPDATE_NAIVE_H
#define AC_PSO_UPDATE_NAIVE_H

#include <entities/particle.h>


/*
 * Naive approach to particle update.
 *
 * Generate two random numbers mu1, mu2 in interval [0.0, 1.0]
 *
 * NewPosition = currPos + currVelocity
 * NewVelocity = currVelocity +
 *              ((pbest - currPos) * (LEARNING_FACTOR * mu1)) +
 *              ((lbest - currPos) * (LEARNING_FACTOR * mu2))
 */
namespace pso
{
    namespace update
    {
        namespace naive
        {
            /*
             * Updates the particle in naive standard way
             */
            void update_naive(Particle* particle);
        }

    }
}

#endif //AC_PSO_UPDATE_NAIVE_H