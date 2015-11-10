//
// Created by jakub on 11/10/15.
//

#ifndef AC_KMEANS_H
#define AC_KMEANS_H

#include <vector>

/*
 * Computes clustering Kmeans algorithm.
 *
 * 1) Randomly select k center
 * 2) Group points to their closest centroids
 * 3) update centroids by computing center of gravity - mean
 * 4) Repeat 2), 3) until convergence or after maximum iterations.
 */
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

    // Each vector is Cluster having a vector of indices
    // Each index i corresponds to the i-th element in the data set.
    std::vector<std::vector<int>> clusterIndices;

    //
    std::vector<int> centroidsIndices;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    // Initializes centroids
    void initCentroids();

    // Update centroids position
    void updateCentroids();

    // Updates clusters based on current centroids position.
    void updateClusters();

    // Checks whether the computation converged.
    bool isConverged();

public:
    KMeans(int k, double tol, int max_iter);

    void compute();

    //-----------------------------------------------------------//
    //  GETTERS / SETTERS
    //-----------------------------------------------------------//

    // Getters
    int getK();
    double getTol();
    int getMaxIter();

    // Setters
    void setK(int k);
    void setTol(double tol);
    void setMaxIter(int max_iter);


};


#endif //AC_KMEANS_H
