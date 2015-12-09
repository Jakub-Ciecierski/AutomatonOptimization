//
// Created by jakub on 12/3/15.
//

#include <stdexcept>
#include <sstream>
#include "transition_function.h"

TransitionFunction::TransitionFunction(unsigned int stateCount,
                                        unsigned int symbolCount) :
                            stateCount(stateCount),
                            symbolCount(symbolCount){
    int size = this->stateCount*this->symbolCount;
    entries.resize(size);

    for(int i = 0; i < size; i++){
        entries[i] = -1;
    }
}

TransitionFunction::TransitionFunction(unsigned int stateCount,
                                       unsigned int symbolCount,
                                       std::vector<int> entries):
                        stateCount(stateCount),
                        symbolCount(symbolCount){
    this->entries = entries;
}

TransitionFunction::TransitionFunction(const TransitionFunction& tf){
    this->stateCount = tf.stateCount;
    this->symbolCount = tf.symbolCount;
    this->entries = tf.entries;
}

TransitionFunction::~TransitionFunction(){
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

unsigned int TransitionFunction::getIndex(const unsigned int state,
                                          const unsigned int symbol) const{
    return symbol*stateCount + state;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const unsigned int& TransitionFunction::getStateCount() const{
    return this->stateCount;
}

const unsigned int& TransitionFunction::getSymbolCount() const{
    return this->symbolCount;
}

int TransitionFunction::getState(const unsigned int fromState,
                                 const unsigned int symbol) const{
    if(fromState < 0 || fromState >= stateCount ||
       symbol < 0 || symbol >= symbolCount){
        std::stringstream ss;
        ss << "FromState = " << fromState << " stateCount = " << stateCount
        << std::endl;
        ss << "Symbol= " << symbol<< " symbolCount = " << symbolCount
        << std::endl;

        throw std::invalid_argument("TransitionFunction::getState\n" +
                                            ss.str());
    }


    return entries[getIndex(fromState, symbol)];
}

void TransitionFunction::addTransition(
                                const unsigned int fromState,
                                const unsigned int symbol,
                                const unsigned int toState){
    if(fromState < 0 || fromState >= stateCount ||
       symbol < 0 || symbol >= symbolCount ||
       toState < 0 || toState >= stateCount) {
        std::stringstream ss;
        ss << "TransitionFunction::addTransition" << std::endl;
        ss << "State Count  = " << stateCount<< std::endl;
        ss << "Symbol Count = " << symbolCount<< std::endl;
        ss << "From State   = " << fromState << std::endl;
        ss << "Symbol       = " << symbol<< std::endl;
        ss << "to state     = " << toState<< std::endl;
                throw std::invalid_argument(ss.str());
        }

    entries[getIndex(fromState, symbol)] = toState;
}

//-----------------------------------------------------------//
//  OPERATORS
//-----------------------------------------------------------//

std::ostream& operator<<(std::ostream& os,
                                const TransitionFunction& tf){
    os << "[ ";

    unsigned int symbolCount = tf.getSymbolCount();
    unsigned int stateCount = tf.getStateCount();


    for(unsigned int i = 0; i < symbolCount; i++){
        os << "[ ";
        for(unsigned int j = 0; j < stateCount; j++){
            os << tf.entries[tf.getIndex(j, i)];
            if(j != stateCount-1)
                os << ", ";
        }
        os << " ]";
        if(i != symbolCount-1)
            os << ", ";
    }

    os << " ]";
    return os;
}