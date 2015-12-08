//
// Created by jakub on 12/1/15.
//

#include <sstream>
#include <logger/log.h>
#include "pso_update_naive.h"
#include "pso_update_common.h"

namespace pso
{
    namespace update
    {
        namespace naive
        {
            void update_naive(Particle *particle) {
                const Point<double> oldPosition(*(particle->getPosition()));
                particle->oldPosition = oldPosition;

                const Point<double> velocity(*(particle->getVelocity()));

                const Point<double>* pbest = particle->getPBest();
                const Point<double>* lbest = particle->getLBest();

                double mu1, mu2;

                mu1 = utils::generateRandomNumber(0.0f, 1.0f);
                mu2 = utils::generateRandomNumber(0.0f, 1.0f);

                Point<double> toPosition = oldPosition + (velocity);

                moveParticleWithMaxVelocity(particle, &toPosition);

                particle->setVelocity(
                        (velocity) + ((*pbest) - (oldPosition)) *
                        (global_settings::LEARNING_FACTOR * mu1)
                        +
                        ((*lbest) - (oldPosition)) *
                        (global_settings::LEARNING_FACTOR * mu2));

            }
        }
    }
}