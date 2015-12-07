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

                std::stringstream ss;
                ss << "Particle Info" << std::endl;
                ss << "lbest:        " << *lbest << std::endl;
                ss << "Old Velocity: " << velocity << std::endl;
                ss << "New Velocity: "
                      << *(particle->getVelocity()) << std::endl;

                ss << "To Position:  " << toPosition << std::endl;
                ss << "Old Position: " << oldPosition << std::endl;
                ss << "New Position: "
                    << *(particle->getPosition()) << std::endl;

                ss << "Delta Pos:    "
                    << *(particle->getPosition()) - oldPosition << std::endl;

                ss << std::endl;

                //logger::log(ss.str());
            }
        }
    }
}