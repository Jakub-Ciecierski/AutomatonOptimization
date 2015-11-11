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

    this->data = data;

    clusterIndices.resize(k);
    for(int i = 0; i < k; i++){
        clusterIndices[i].resize(0);
    }
    centroids.resize(k);





    int t;

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


template <class T>
void KMeans<T>::initCentroids(){
    for(int i = 0; i < k; i++){
        centroids[i] = (*data)[i];
    }
}

template <class T>
void KMeans<T>:: updateCentroids(){
    clusterIndices.clear();
}

template <class T>
void KMeans<T>::updateClusters(){

}

template <class T>
bool KMeans<T>::isConverged(){

}


//-----------------------------------------------------------//
//  EXPLICIT INSTANTIATING
//-----------------------------------------------------------//

template class KMeans<char>;
template class KMeans<int>;
template class KMeans<float>;
template class KMeans<double>;