//
// Created by jakub on 11/24/15.
//

#ifndef AC_PSO_PARALLEL_H
#define AC_PSO_PARALLEL_H

#include <words_generator.h>
#include "particle.h"

/*
 * PSO Multi-threaded solution for fitness function
 */
namespace pso_parallel
{

    /*
     * Structure of thread data
     */
    struct thread_args {
        thread_args() { }

        int id;
        int thread_count;

        vector<Particle *> *particles;
        std::vector<Particle *> *bestParticles;
        double *globalBestFitness;

        WordsGenerator *wordsGenerator;
        vector<int> *toolRelationResults;

        pthread_mutex_t *mutex;
    };

    namespace fitness
    {
        /*
         * Starts the computations of parallel fitness function
         */
        void *initFitnessFunction(void *);

        /*
         * Calculates pbest and fitness value for each particle
         */
        void calculatePBestAndFitness(int start, int finish,
                                      thread_args *t_args);

        /*
         * Computes fitness function
         */
        double fitnessFunction(Particle *p, WordsGenerator *wg,
                               vector<int> *toolRelationResults);

        /*
         * Calculates the global best fitness among the particles
         */
        void calculateGBestFitness(Particle *particle,
                                   std::vector<Particle *> *bestParticles,
                                   double *globalBestFitness);
    }
}

#endif //AC_PSO_PARALLEL_H
