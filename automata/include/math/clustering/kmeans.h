//
// Created by jakub on 11/10/15.
//

#ifndef AC_KMEANS_H
#define AC_KMEANS_H

#include <vector>
#include "point.h"

/*
 * Computes clustering Kmeans algorithm.
 *
 * 1) Randomly select k center
 * 2) Group points to their closest centroids
 * 3) update centroids by computing center of gravity - mean
 * 4) Repeat 2), 3) until convergence or after maximum iterations.
 *
 * TODO Parallel
 */
template <class T>
class KMeans {

private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Number of clusters
    int k;

    // The distance limit before converging
    double tol;

    // Maximum number of iteration
    int max_iter;

    // Number of dimension of the data;
    int dataDimension;

    // Each vector is Cluster having a vector of indices
    // Each index i corresponds to the i-th element in the data set.
    std::vector<std::vector<int>> clusterIndices;

    // Centroid of each cluster
    std::vector<Point<T>> centroids;

    // The centroids of previous iteration.
    std::vector<Point<T>> previousCentroids;

    // Point to the data to be cluster
    const std::vector<Point<T>>* data;

    // Vector of clusters, each contating points
    // This should be a vector of pointers to points TODO
    std::vector<std::vector<Point<T>>> clusters;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Initializes centroids with kmeans++ algorithm
     */
    void kmeans_pp();

    /*
     * Choose next centroid, used in kmeans_pp
     */
    void chooseCentroid(int &centroidCount);

    /*
     * Update centroids position
     */
    void updateCentroids();

    /*
     * Updates clusters based on current centroids position.
     */
    void updateClusters();

    /*
     * Checks whether the computation converged.
     */
    bool isConverged(const int& t);

    void createClusters();

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    KMeans(int k, double tol, int max_iter);
    KMeans(const KMeans& cpy);

    ~KMeans();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts the computations
     */
    void compute(const std::vector<Point<T>>* data);

    //-----------------------------------------------------------//
    //  GETTERS / SETTERS
    //-----------------------------------------------------------//

    /*
     * Returns i-th cluster.
     * The valid range of i = [0, k-1]
     */
    std::vector<Point<T>> getCluster(int i);

    int getK();
    double getTol();
    int getMaxIter();

    void setK(int k);
    void setTol(double tol);
    void setMaxIter(int max_iter);
};


#endif //AC_KMEANS_H
