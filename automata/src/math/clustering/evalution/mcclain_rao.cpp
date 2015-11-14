//
// Created by jakub on 11/14/15.
//

#include "mcclain_rao.h"
#include "global_settings.h"
#include "logger.h"
#include "geometry.h"
#include <cstring>
#include <stdexcept>

template <class T>
McClainRao<T>::McClainRao(int start_k, int end_k)
        : start_k(start_k), end_k(end_k) {
}

template <class T>
McClainRao<T>::~McClainRao(){
    delete(best_km);
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

/*
 * Starts the computation for mcclain-rao index
 */
template <class T>
void McClainRao<T>::compute(const std::vector<Point<T>>* data) {
    this->data = data;
    this->best_C = -1;

    if(this->data == NULL){
        throw std::invalid_argument("NULL Pointer");
    }

    LOG_DEBUG("Mcclain-Rao Starting");

    // Iterate through a fixed interval of possible values of k
    for (int k = start_k; k <= end_k; k++){
        km = new KMeans<T>(k,
                           global_settings::KM_TOL,
                           global_settings::KM_MAX_ITER);
        // Compute clustering
        km->compute(data);

        // Compute the sum within
        computeSumWithin();

        // Compute the sum between
        computeSumBetween();

        double C = (this->sumWithin/this->nw) / (this->sumBetween/this->nb);

        std::cout << "mc-r(" << k << ") = " << C << std::endl;

        if(best_C > C || best_C == -1){
            best_C = C;

            best_km = new KMeans<T>(*km);
        }

        delete km;
    }
    std::cout << "Best K: " << best_km->getK() << std::endl;
    LOG_DEBUG("Mcclain-Rao Finished");
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

template <class T>
void McClainRao<T>::computeSumWithin() {
    this->sumWithin = 0;
    this->nw = 0;

    LOG_DEBUG("McR: SumWithin Starting");

    // For each cluster
    for(int c = 0; c < km->getK(); c++){
        std::vector<Point<T>> cluster = km->getCluster(c);
        int size = cluster.size();

        for(int i = 0; i < size-1; i++){
            for(int j = i+1; j < size; j++){
                this->sumWithin += acm::euclideanDistance(cluster[i],
                                                          cluster[j]);
                this->nw++;
            }
        }
    }

    LOG_DEBUG("McR: SumWithin Finished");
}

template <class T>
void McClainRao<T>::computeSumBetween() {
    this->sumBetween = 0;
    this->nb = 0;

    LOG_DEBUG("McR: SumBetween Starting");

    // Number of clusters
    int k = km->getK();

    // For each distinct pair of clusters
    for(int c1 = 0; c1 < k-1; c1++){
        std::vector<Point<T>> cluster1 = km->getCluster(c1);
        for(int c2 = c1+1; c2 < k; c2++){
            std::vector<Point<T>> cluster2 = km->getCluster(c2);
            // For each pair of points from cluster1 and cluster2
            for(unsigned int i = 0;i < cluster1.size(); i++){
                for(unsigned int j = 0; j < cluster2.size(); j++){
                    this->sumBetween += acm::euclideanDistance(cluster1[i],
                                                               cluster2[j]);
                    this->nb++;
                }
            }
        }
    }
    LOG_DEBUG("McR: SumBetween Finished");
}

//-----------------------------------------------------------//
//  EXPLICIT TEMPLATE INSTANTIATING
//-----------------------------------------------------------//

template class McClainRao<char>;
template class McClainRao<int>;
template class McClainRao<float>;
template class McClainRao<double>;