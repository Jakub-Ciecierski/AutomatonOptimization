//
// Created by jakub on 12/3/15.
//

#include "fuzzy_transition_settings.h"
#include "fuzzy_transition_function.h"
#include "logger/log.h"
#include <stdexcept>


FuzzyTransitionFunction::FuzzyTransitionFunction(unsigned stateCount,
                                       unsigned symbolCount) :
                        stateCount(stateCount),
                        symbolCount(symbolCount){

    // As many Matrices as symbols
    this->entries.resize(this->symbolCount);

    // Initiate each Matrix
    for(unsigned int i = 0; i < this->symbolCount; i++){
        this->entries[i] = new Matrix<float>(stateCount, stateCount);
    }
}

FuzzyTransitionFunction::FuzzyTransitionFunction(
                                const FuzzyTransitionFunction& tf):
        stateCount(tf.stateCount),
        symbolCount(tf.symbolCount){

    // As many Matrices as symbols
    this->entries.resize(this->symbolCount);

    // Initiate each Matrix
    for(unsigned int i = 0; i < this->symbolCount; i++){
        this->entries[i] = new Matrix<float>(*(tf.getTransitionMatrix(i)));
    }
}

FuzzyTransitionFunction::~FuzzyTransitionFunction(){
    // Initiate each Matrix
    for(unsigned int i = 0; i < this->symbolCount; i++){
        delete this->entries[i];
    }
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const unsigned int& FuzzyTransitionFunction::getStateCount() const{
    return this->stateCount;
}

const unsigned int& FuzzyTransitionFunction::getSymbolCount() const{
    return this->symbolCount;
}

const Matrix<float>* const
FuzzyTransitionFunction::getTransitionMatrix(unsigned symbol) const{
    if(symbol < 0 || symbol >= symbolCount)
        throw std::invalid_argument("TransitionFunction::getTransitionMatrix");

    return this->entries[symbol];
}

void FuzzyTransitionFunction::addTransition(const unsigned int fromState,
                                       const unsigned int symbol,
                                       const unsigned int toState,
                                       const float fazziness){
    if(fromState < 0 || fromState >= stateCount ||
            symbol < 0 || symbol >= symbolCount ||
            toState < 0 || toState >= stateCount ||
            fazziness < transition_settings::FUZZY_MIN ||
            fazziness > transition_settings::FUZZY_MAX)
        throw std::invalid_argument("TransitionFunction::addTransition");

    Matrix<float>* matrix = this->entries[symbol];

    (*matrix)[fromState][toState] = fazziness;
}

float FuzzyTransitionFunction::getStateFazziness(const unsigned int fromState,
                                            const unsigned int symbol,
                                            const unsigned int toState) const{
    if(fromState < 0 || fromState >= stateCount ||
       symbol < 0 || symbol >= symbolCount ||
       toState < 0 || toState >= stateCount)
        throw std::invalid_argument("TransitionFunction::getFazzyValue");

    Matrix<float>* matrix = this->entries[symbol];

    return (*matrix)[fromState][toState];
}

//-----------------------------------------------------------//
//  OPERATORS
//-----------------------------------------------------------//

std::ostream& operator<<(std::ostream& os,
                                const FuzzyTransitionFunction& tf){
    unsigned int symbolCount = tf.symbolCount;

    for(unsigned int i = 0; i < symbolCount; i++){
        Matrix<float>* matrix = tf.entries[i];

        os << "Symbol: " << i << std::endl;
        os << *matrix;
    }
    return os;
}
