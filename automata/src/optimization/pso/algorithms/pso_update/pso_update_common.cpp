//
// Created by jakub on 12/1/15.
//

#include <entities/random_sphere.h>
#include <algorithms/pso_update/pso_update_naive.h>
#include <algorithms/pso_update/pso_update_sphere.h>
#include <logger/log.h>
#include "pso_update_common.h"

namespace pso
{
    namespace update
    {
        void updateParticles(std::vector<Particle*>* particles){
            unsigned long size = particles->size();
            for(unsigned long i = 0; i < size; i ++){
                Particle* p = (*particles)[i];
                naive::update_naive(p);

                boundPositionWithInterval(p);
                p->updateCurrentDFA();
            }
        }

        void moveParticleWithMaxVelocity(Particle* particle,
                                         Point<double>* toPos){
            double maxVelocity = particle->getMaxVelocity();

            const Point<double>* position = particle->getPosition();
            Point<double> newPosition(position->size());

            for(int i = 0;i < toPos->size(); i++){
                int sign;

                sign = 1;
                double delta = ((*position)[i] - (*toPos)[i]);
                if (delta < 0)
                    sign = -1;

                delta *= delta;
                delta = sqrt(delta);

                if(delta > maxVelocity){
                    newPosition[i] =
                            (*position)[i] -
                            (maxVelocity*sign);
                }
                else{
                    newPosition[i] = (*toPos)[i];
                }
            }

            particle->setPosition(newPosition);
        }

        void boundPositionWithInterval(Particle* particle){
            const Point<double>* position = particle->getPosition();

            const double intervalMin = particle->getIntervalMin();
            const double intervalMax = particle->getIntervalMax();

            // For each dimension check if the position is out of
            // solution space. If yes put it back on the edge
            // and reset the velocity
            for(int i = 0; i < position->size(); i++) {
                if((*position)[i] < intervalMin) {
                    particle->setPositionDim(intervalMin, i);
                    particle->setVelocityDim(0, i);
                }

                if((*position)[i] > intervalMax) {
                    particle->setPositionDim(intervalMax, i);
                    particle->setVelocityDim(0, i);
                }

            }
        }
    }
}
