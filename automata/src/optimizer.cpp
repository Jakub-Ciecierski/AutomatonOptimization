//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Optimizer::Optimizer() {
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Optimizer::start() {
    // 1) Generate sample set of words
    generateWords();

    // 2) Compute the relation R-L and save the results
    computeRelation();

    // 3) Run PSO instances
    for(int s = global_settings::MIN_STATES;
            s < global_settings::MIN_STATES; s++){

    }

}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Optimizer::generateWords() {
}

void Optimizer::computeRelation() {
}

void Optimizer::runPSO() {
}