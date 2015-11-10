//
// Created by jakub on 11/10/15.
//

#include "kmeans.h"

kmeans::kmeans(int k, double tol, int max_iter) :
        k(k), tol(tol), max_iter(max_iter) { }

int kmeans::getK() {
    return this->k;
}

int kmeans::getMaxIter() {
    return this->max_iter;
}

double kmeans::getTol() {
    return this->tol;
}

void kmeans::compute() {

}