//
// Created by jakub on 12/1/15.
//

#include "pso_update.h"

namespace pso
{
    namespace update
    {
        void updateParticles(std::vector<Particle*>* particles){
            unsigned long size = particles->size();
            for(unsigned long i = 0; i < size; i ++){
                (*particles)[i]->update();
            }
        }
    }
}