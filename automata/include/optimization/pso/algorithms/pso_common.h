//
// Created by jakub on 11/24/15.
//

#ifndef AC_PSO_COMMON_H
#define AC_PSO_COMMON_H

#include "words_generator.h"
#include "particle.h"

/*
 * The main hub for PSO Algorithm module.
 * Contains all common data shared among all other algorithms within
 * this module.
 */
namespace pso
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

    /*
     * Used to measure time during computations
     */
    struct TimeMeasures
    {
        double neighbouthoodTime;
        double fitnessTime;
        double updateParticleTime;
    };
}

#endif //AC_PSO_PARALLEL_H
