//
// Created by jakub on 11/10/15.
//
/*
 * Since templates are the most stupid thing. The functions have to be defined
 * in the header file or explicit initializing of template for specific type
 * has to be included at the end of .cpp file. The latter approach has been
 * applied.
 *
 * http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
 */
#include "kmeans.h"
#include "geometry.h"   /* distance */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

template <class T>
KMeans<T>::KMeans(int k, double tol, int max_iter) :
        k(k), tol(tol), max_iter(max_iter) {
}

template <class T>
KMeans<T>::~KMeans() {

}


//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

template <class T>
void KMeans<T>::compute(std::vector<Point<T>>* data) {
    int t;

    if((*data).size() == 0)
        return;

    this->data = data;
    this->dataDimension = (*data)[0].size();

    // Start with initializing centroids and assigning points to them
    initCentroids();
    updateClusters();

    t = 0;
    while(!isConverged() && t < max_iter){
        updateCentroids();

        updateClusters();
    }
}

//-----------------------------------------------------------//
//  GETTERS / SETTERS
//-----------------------------------------------------------//

template <class T>
int KMeans<T>::getK() {
    return this->k;
}

template <class T>
int KMeans<T>::getMaxIter() {
    return this->max_iter;
}

template <class T>
double KMeans<T>::getTol() {
    return this->tol;
}

//-----------------------------------------------------------//

template <class T>
void KMeans<T>::setK(int k) {
    this->k = k;
}

template <class T>
void KMeans<T>::setMaxIter(int max_iter) {
    this->max_iter = max_iter;
}

template <class T>
void KMeans<T>::setTol(double tol) {
    this->tol = tol;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

/*
 * Computes initial values for centroids.
 * The kmeans++ algorithm is used.
 *
 * 1) Choose one center uniformly at random from among the data point.
 *
 * 2) For each data point x, compute D(x), the distance between x and
 *      the nearest center that has already been chosen.
 *
 * 3) Choose one new data point at random as new center, using a weighted
 *      probability distribution where a point x is chosen with
 *      probability proportional to D(x)^2
 *
 * 4) Repeat steps 2) and 3) until k centers have chosen.
 *
 */
template <class T>
void KMeans<T>::initCentroids(){
    int centroidCount;
    int dataSize;

    srand(time(NULL));

    // Current centroid count, must reach value k
    centroidCount = 0;
    dataSize = (*data).size();
    // Clear centroids
    this->centroids.clear();
    this->centroids.resize(k);

    /* 1) Choose first center. */
    // Generates random number between [0, dataSize-1]
    int centerIndex = rand() % (dataSize);
    Point<T> center = (*data)[centerIndex];
    this->centroids[centroidCount++] = center;

    while(centroidCount < k){
        /* 2) Compute D(x) */

        double sumOfSquaredDist= 0;
        std::vector<double> squaredDist(dataSize);

        // For each point find the distance to closest center.
        for(int i = 0;i < dataSize; i++){
            double minDistance;
            int minIndex;

            minIndex = 0;
            minDistance = acm::distance(this->centroids[minIndex], (*data)[i]);

            for(int j = 0;j < centroidCount; j++){
                double distance = acm::distance(this->centroids[j], (*data)[i]);
                if(minDistance >= distance ){
                    minDistance = distance;
                    minIndex = j;
                }
            }
            squaredDist.push_back(minDistance*minDistance);
            sumOfSquaredDist += minDistance * minDistance;
        }

        /* 3) Weighted Distribution TODO */
    }
    for(int i = 0; i < k; i++){
        centroids[i] = (*data)[i];
    }
}

/*
 * Updating centroids.
 * Save the previous centroids.
 * Compute new ones based on the center of gravity of the cluster.
 */
template <class T>
void KMeans<T>::updateCentroids(){
    int clusterSize;

    // Save the previous centroids
    this->previousCentroids = this->centroids;

    // Compute the center of gravity of each cluster.
    for(int i = 0;i < this->k; i++){
        Point<T> centroid(this->dataDimension);
        clusterSize = this->clusterIndices[i].size();

        for(int j = 0; j < clusterSize; j++){
            int l = this->clusterIndices[i][j];
            centroid += (*data)[l];
        }

        centroid /= clusterSize;
        this->centroids[i] = centroid;
    }
}

/*
 * Cluster is updated. Each point in data finds the closest centroid.
 * Point which is assigned k-th centroid, belongs to k-th cluster
 */
template <class T>
void KMeans<T>::updateClusters(){
    int minClusterIndex;
    double distance, minClusterDistance;
    int dataSize;

    dataSize = (*data).size();

    // Clear the indices
    this->clusterIndices.clear();
    this->clusterIndices.resize(k);

    // For each point in data, find its closest centroid
    for(int i = 0;i < dataSize;i++){
        Point<T> point = (*data)[i];

        minClusterIndex = 0;
        minClusterDistance = acm::distance(point,
                                           this->centroids[minClusterIndex]);

        // Find closest centroid
        for(int j = 0;j < k; j++){
            distance = acm::distance(point, this->centroids[j]);

            if(minClusterDistance >= distance){
                minClusterDistance = distance;
                minClusterIndex = j;
            }
        }
        this->clusterIndices[minClusterIndex].push_back(i);
    }

}

/*
 * KMeans is converged when all centroids have not repositioned by more than
 * tol value since last iteration
 */
template <class T>
bool KMeans<T>::isConverged(){
    int flags;
    double distance;

    // When flags reaches value k, then all centroids have converged.
    flags = 0;
    for(int i = 0;i < this->k; i++){
        distance = acm::distance(this->centroids[i],
                                 this->previousCentroids[i]);

        if(distance <= this->tol)
            flags++;
    }

    return flags == k;
}

//-----------------------------------------------------------//
//  EXPLICIT INSTANTIATING
//-----------------------------------------------------------//

template class KMeans<char>;
template class KMeans<int>;
template class KMeans<float>;
template class KMeans<double>;