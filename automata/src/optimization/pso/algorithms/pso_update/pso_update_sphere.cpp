//
// Created by jakub on 12/1/15.
//

#include <entities/random_sphere.h>
#include "pso_update_sphere.h"
#include "pso_update_common.h"

namespace pso
{
    namespace update
    {
        namespace sphere
        {
            void update_sphere(Particle *particle) {
                // Get three points
                Point<double> oldPosition = particle->_position;
                Point<double> y_p1 = (particle->pbest - oldPosition)
                                     * global_settings::LEARNING_FACTOR;

                Point<double> y_p2 = (particle->lbest - oldPosition)
                                     * (global_settings::LEARNING_FACTOR);

                // Calculate center of gravity between these points
                Point<double> centerOfGravity =
                        (oldPosition + y_p1 + y_p2) / 3.0;
                // Generate a random point within a sphere
                Point<double> randomPointInSphere =
                        generateRandomPointInSphere(centerOfGravity,
                                                    oldPosition);

                // Calculate new position
                Point<double> toPosition =
                        (particle->_velocity *
                        global_settings::PARTICLE_VEL_WEIGHT)
                        + randomPointInSphere;

                moveParticleWithMaxVelocity(particle, &toPosition);

                particle->_velocity =
                        (particle->_velocity *
                         global_settings::PARTICLE_VEL_WEIGHT)
                        + randomPointInSphere - oldPosition;
            }

            Point<double> generateRandomPointInSphere(
                                Point<double> centerOfGravity,
                                Point<double> oldPosition) {
                Point<double> randomPointWithinSphere;
                RandomSphere randomSphere(centerOfGravity, oldPosition);
                randomPointWithinSphere = randomSphere.generatePointWithin();
                return randomPointWithinSphere;
            }
        }
    }
}