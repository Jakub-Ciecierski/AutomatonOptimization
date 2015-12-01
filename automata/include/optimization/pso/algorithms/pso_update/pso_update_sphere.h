//
// Created by jakub on 12/1/15.
//

#ifndef AC_PSO_UPDATE_SPHERE_H
#define AC_PSO_UPDATE_SPHERE_H

#include <entities/particle.h>

/*
 * Functionality of updating the particle using random sphere generation.
 *
 * Take Center of gravity G of three points:
 *      1) Current position: currPos
 *      2) Modified pbest
 *      3) Modified lbest
 *
 * Create a sphere with center G and radius [G - (current position)]
 *
 * Generate a random point randPos within the sphere.
 *
 * newPosition = (current_velocity * VEL_WEIGHT) + randPos
 * newVelocity = (current_velocity * VEL_WEIGHT) + randPos-currPos
 *
 */
namespace pso
{
    namespace update
    {
        namespace sphere
        {
            /*
             * Update particle
             */
            void update_sphere(Particle *particle);

            /*
             * Generator Random point within sphere.
             */
            Point<double> generateRandomPointInSphere(
                            Point<double> centerOfGravity,
                            Point<double> oldPosition);
        }
    }
}


#endif //AC_PSO_UPDATE_SPHERE_H
