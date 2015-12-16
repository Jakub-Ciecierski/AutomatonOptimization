//
// Created by jakub on 12/1/15.
//

#include <clustering/evaluation/mcclain_rao.h>
#include <settings/global_settings.h>
#include <entities/particle.h>
#include "pso_common.h"
#include "pso_neighbourhood.h"

namespace pso
{
    namespace nbhood
    {
        void updateNeighbourhoods(std::vector<Particle*>* particles,
                                std::vector<const Point<double>*>*
                                    particlePositions,
                                int& lastNumberOfClusters) {
            // Compute cluster evaluation.
            McClainRao<double> mc_r(global_settings::START_K,
                                    global_settings::END_K);
            mc_r.compute(particlePositions);

            // Get the most optimal clustering
            KMeans<double> *km = mc_r.getBestClustering();
            // save the result to log
            lastNumberOfClusters = km->getK();

            // For each neighbourhood (cluster), find the lbest
            for (int c = 0; c < km->getK(); c++) {

                const std::vector<int>* clusterIndices =
                                                km->getClusterIndices(c);

                if(clusterIndices->size() == 0) continue;

                int bestIndex = (*clusterIndices)[0];
                double bestFitness = (*particles)[bestIndex]->getBestFitness();

                // Find lbest
                for (unsigned int i = 0; i < clusterIndices->size(); i++) {
                    int index = (*clusterIndices)[i];
                    double currBestFitness =
                            (*particles)[index]->getBestFitness();

                    if (bestFitness < currBestFitness) {
                        bestFitness = currBestFitness;
                        bestIndex = index;
                    }
                }

                // Assign lbest to each particle
                for (unsigned int i = 0; i < clusterIndices->size(); i++) {
                    int index = (*clusterIndices)[i];
                    (*particles)[index]->setLBest(
                            (*(*particles)[bestIndex]->getPosition()));
                }
            }
        }
    }
}

