//
// Created by jakub on 12/1/15.
//

#include "pso_update_naive.h"
#include "pso_update_common.h"

namespace pso
{
    namespace update
    {
        namespace naive
        {
            void update_naive(Particle *particle) {
                Point<double> oldPosition = particle->_position;
                double mu1, mu2;

                mu1 = utils::generateRandomNumber(0.0f, 1.0f);
                mu2 = utils::generateRandomNumber(0.0f, 1.0f);

                Point<double> toPosition =
                        particle->_position +
                        particle->_velocity;

                moveParticleWithMaxVelocity(particle, &toPosition);

                particle->_velocity =
                        particle->_velocity +
                        (particle->pbest - oldPosition) *
                        (global_settings::LEARNING_FACTOR * mu1)
                        +
                        (particle->lbest - oldPosition) *
                        (global_settings::LEARNING_FACTOR * mu2);
            }
        }
    }
}