//
// Created by jakub on 12/1/15.
//

#ifndef AC_PSO_NEIGHBOURHOOD_H
#define AC_PSO_NEIGHBOURHOOD_H

#endif //AC_PSO_NEIGHBOURHOOD_H

/*
 * Contains all the algorithms needed to compute neighbourhood:
 *
 * Updates the state of neighbourhoods.
 * The data set in the form of all particles
 * are subjected to cluster analysis.
 *
 * 1) Find the optimal number of clusters k.
 * 2) Compute kmeans for that k.
 * 3) Each cluster is a single neighbourhood.
 */

namespace pso
{
    namespace nbhood
    {
        /*
         * Updates the state of neighbourhoods.
         * The data set in the form of all particles
         * are subjected to cluster analysis.
         *
         * 1) Find the optimal number of clusters k.
         * 2) Compute kmeans for that k.
         * 3) Each cluster is a single neighbourhood.
         *
         */
        void updateNeighbourhoods(std::vector<Particle*>* particles,
                                  vector<const Point<double>*>*
                                        particlePositions,
                                  int& lastNumberOfClusters);
    }
}