//
// Created by jakub on 12/1/15.
//

#include <entities/random_sphere.h>
#include <algorithms/pso_update/pso_update_naive.h>
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
                p->updateDFARepresentation();
            }
        }

        void moveParticleWithMaxVelocity(Particle* particle,
                                         Point<double>* toPos){
            for(int i = 0;i < toPos->size(); i++){
                int sign;

                sign = 1;
                double delta = (particle->_position[i] - (*toPos)[i]);
                if (delta < 0)
                    sign = -1;

                delta *= delta;
                delta = sqrt(delta);

                if(delta > particle->_maxVelocity){
                    particle->_position[i] =
                            particle->_position[i] -
                            (particle->_maxVelocity*sign);
                }
                else{
                    particle->_position[i] = (*toPos)[i];
                }
            }
        }

        void boundPositionWithInterval(Particle* particle){
            Point<double>* position = &(particle->_position);

            // For each dimension check if the position is out of
            // solution space. If yes put it back on the edge
            // and reset the velocity
            for(int i = 0; i < position->size(); i++) {
                if((*position)[i] < particle->_intervalMin) {
                    (*position)[i] = particle->_intervalMin;
                    particle->_velocity[i] = 0;
                }

                if((*position)[i] > particle->_intervalMax) {
                    (*position)[i] = particle->_intervalMax;
                    particle->_velocity[i] = 0;
                }

            }
        }
    }
}