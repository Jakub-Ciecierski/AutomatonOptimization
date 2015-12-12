//
// Created by jakub on 12/1/15.
//

#include "pso_fitness.h"
#include <error.h>
#include <algorithm>
#include <relation_induced.h>

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

                p->setFitness(fitnessValue(p, t_args->wordsGenerator,
                                          t_args->toolRelationResults));

                // Check if particle is in new pbest
                if (p->getBestFitness() < p->getFitness()) {
                    p->saveCurrentConfigAsBest();
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
            double count = 0;
            int pairCount = 0;

            const DFA* dfa = p->getCurrentDFA();

            const vector<Word*>* trainingSet = wg->getTrainingAllSet();
            unsigned int wordCount = trainingSet->size();

            vector<int> stateVector(wordCount);
            // Pre compute all words. Save results in stateVector
            for(unsigned int i = 0; i < wordCount; i++){
                Word* word = (*trainingSet)[i];
                stateVector[i] = dfa->compute(*word);
            }

            // For all distinct pairs
            for(unsigned int i = 0; i < wordCount-1; i++){
                for(unsigned int j = i+1; j < wordCount; j++){
                    bool inRelation = stateVector[i] == stateVector[j];
                    int result = inRelation ? 1:0;
                    count += (result ==
                                    (*toolRelationResults)[pairCount]) ? 1 : 0;

                    pairCount++;
                }
            }

            return count / (double) pairCount;
        }

        void calculateGBestFitness(Particle* particle,
                                   std::vector<Particle*>* bestParticles,
                                   double* globalBestFitness)
        {

            double currentFitness = particle->getFitness();

            // Check if another particle has global fitness
            if (*globalBestFitness == currentFitness) {
                // If that particle is not already here
                if (std::find(bestParticles->begin(), bestParticles->end(),
                              particle) == bestParticles->end()) {
                    bestParticles->push_back(particle);
                }
            }

            else if (*globalBestFitness < currentFitness) {
                bestParticles->clear();

                *globalBestFitness = currentFitness;

                bestParticles->push_back(particle);
            }
        }
    }
}