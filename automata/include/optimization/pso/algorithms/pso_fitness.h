//
// Created by jakub on 12/1/15.
//

#ifndef AC_PSO_FITNESS_H
#define AC_PSO_FITNESS_H

#include "words_generator.h"
#include "particle.h"
#include "pso_common.h"

/*
 * Contains parallel implementation of fitness function update.
 *
 * Parallel Solution:
 *      Each thread is assigned a interval which it should operate on.
 *
 * Each particle is decoded back to DFA.
 * Each DFA computes all the pairs of words that check how they relate to
 * the original tool, thus calculating the error.
 */

namespace pso
{
    namespace fitness
    {
        /*
         * Starts the computations of parallel fitness function
         */
        void* initFitness(void *);

        /*
         * Calculates pbest and fitness value for each particle
         */
        void calculatePBestAndFitness(int start, int finish,
                                      pso::thread_args *t_args);

        /*
         * Computes fitness function
         */
        double fitnessValue(Particle *p,
                            WordsGenerator *wg,
                            vector<int> *toolRelationResults);

        /*
         * Calculates the global best fitness among the particles
         */
        void calculateGBestFitness(Particle *particle,
                                   std::vector<Particle *> *bestParticles,
                                   double *globalBestFitness);
    }
}

#endif //AC_PSO_FITNESS_H