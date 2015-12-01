//
// Created by jakub on 12/1/15.
//

#include "pso_fitness.h"
#include <error.h>
#include <algorithm>

namespace pso
{
    namespace fitness
    {
        void* initFitness(void *argv)
        {
            thread_args* t_args = (thread_args*)argv;

            /*          Critical section           */
            if (pthread_mutex_lock(t_args->mutex) != 0)
                ERR("pthread_mutex_lock");

            // Get data to calculate interval
            int id                              = t_args->id;
            int thread_count                    = t_args->thread_count;
            vector<Particle*>* particles        = t_args->particles;

            int particleCount                   = (*particles).size();

            // Check if it is divided evenly
            int reminder = particleCount % thread_count;

            // Give every  thread its unique interval
            int sub_count = particleCount / thread_count;
            int start   = id * sub_count;
            int finish  = start + sub_count - 1;

            // Add indices not given yet to the last thread.
            if(id == thread_count - 1)
                finish += reminder;

            /*          End of Critical section           */
            pthread_mutex_unlock(t_args->mutex);

            calculatePBestAndFitness(start, finish, t_args);

            return NULL;
        }

        void calculatePBestAndFitness(int start, int finish,
                                      thread_args* t_args)
        {
            vector<Particle*>* particles = t_args->particles;

            // Start main loop
            for (int i = start; i <= finish; i++) {

                Particle* p = (*particles)[i];

                p->fitness = fitnessValue(p, t_args->wordsGenerator,
                                          t_args->toolRelationResults);

                // Check if particle is in new pbest
                if (p->bestFitness < p->fitness) {
                    p->pbest = p->_position;
                    p->bestFitness = p->fitness;
                }

                /*          Critical section           */
                if (pthread_mutex_lock(t_args->mutex) != 0)
                    ERR("pthread_mutex_lock");

                // Update global best fitness value
                calculateGBestFitness(p, t_args->bestParticles,
                                      t_args->globalBestFitness);

                /*          End of Critical section           */
                pthread_mutex_unlock(t_args->mutex);
            }
        }

        double fitnessValue(Particle *p, WordsGenerator *wg,
                            vector<int> *toolRelationResults)
        {
            vector<PairOfWords>* pairs = wg->getPairs();

            double count = 0;

            unsigned int pairsSize = pairs->size();
            for (unsigned int i = 0; i < pairsSize; i++) {
                PairOfWords* pair = &((*pairs)[i]);

                Word w1 = pair->word1;
                Word w2 = pair->word2;

                bool inRelation =
                        p->_particleRepresentation->
                                checkRelationInducedByLanguage(w1, w2);

                int result = (inRelation) ? 1 : 0;
                count += (result == (*toolRelationResults)[i]) ? 1 : 0;
            }

            return count / (double) pairsSize;
        }

        void calculateGBestFitness(Particle* particle,
                                   std::vector<Particle*>* bestParticles,
                                   double* globalBestFitness)
        {

            // Check if another particle has global fitness
            if (*globalBestFitness == particle->fitness) {
                // If that particle is not already here
                if (std::find(bestParticles->begin(), bestParticles->end(),
                              particle) == bestParticles->end()) {
                    bestParticles->push_back(particle);
                }
            }

            else if (*globalBestFitness < particle->fitness) {
                bestParticles->clear();

                *globalBestFitness = particle->fitness;

                bestParticles->push_back(particle);
            }
        }
    }
}