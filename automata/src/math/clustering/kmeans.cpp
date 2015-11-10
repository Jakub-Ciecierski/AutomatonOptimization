//
// Created by jakub on 11/10/15.
//

#include "kmeans.h"

KMeans::KMeans(int k, double tol, int max_iter) :
        k(k), tol(tol), max_iter(max_iter) { }

int KMeans::getK() {
    return this->k;
}

int KMeans::getMaxIter() {
    return this->max_iter;
}

double KMeans::getTol() {
    return this->tol;
}

void KMeans::compute() {

}