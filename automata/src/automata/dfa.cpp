//
// Created by jakub on 12/3/15.
//

#include "dfa.h"

DFA::DFA(TransitionFunction* tf) :
        transitionFunction(tf){
    initialState = 0;

    this->acceptingStates = new std::vector<unsigned int>();

    this->checkDeterminism();

    this->createAlphabet(this->getSymbolCount());
}

DFA::DFA(TransitionFunction* tf, unsigned int initialState):
        transitionFunction(tf), initialState(initialState){
    this->acceptingStates = new std::vector<unsigned int>();

    this->checkDeterminism();

    this->createAlphabet(this->getSymbolCount());
}

DFA::DFA(const DFA & dfa){
    this->transitionFunction =
            new TransitionFunction(*(dfa.transitionFunction));

    this->alphabet = new std::vector<int>(dfa.getSymbolCount());
    const std::vector<int>* oldAlphabet = dfa.getAlphabet();

    for(unsigned int i = 0; i < dfa.getSymbolCount(); i++){
        (*this->alphabet)[i] = (*oldAlphabet)[i];
    }

    this->initialState = dfa.getInitialState();

    this->acceptingStates =
            new std::vector<unsigned int>(*(dfa.getAcceptingStates()));
}

DFA::~DFA(){
    delete this->alphabet;
    delete this->transitionFunction;
    delete this->acceptingStates;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void DFA::createAlphabet(unsigned int symbolCount){
    alphabet = new std::vector<int>(symbolCount);

    for(unsigned int i = 0; i < symbolCount; i++){
        (*alphabet)[i] = i;
    }
}

void DFA::  checkDeterminism(){
    for(unsigned int i = 0; i < this->getStateCount(); i++){
        for(unsigned int j = 0; j < this->getSymbolCount(); j++){
            int toState = this->transitionFunction->getState(i, j);
            if(toState < 0 || toState >= (int)this->getStateCount()) {
                throw std::invalid_argument("Determinism not satisfied "
                                                    "DFA_T::checkDeterminism");
            }
        }
    }
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const TransitionFunction* DFA::getTransitionFunction() const{
    return (this->transitionFunction);
}

const std::vector<unsigned int>* DFA::getAcceptingStates() const{
    return (this->acceptingStates);
}

std::vector<int>*DFA::getAlphabet() const {
    return (this->alphabet);
}

const unsigned int&DFA::getStateCount() const{
    return this->transitionFunction->getStateCount();
}

const unsigned int&DFA::getSymbolCount() const{
    return this->transitionFunction->getSymbolCount();
}

const unsigned int&DFA::getInitialState() const{
    return this->initialState;
}

int DFA::compute(const Word& w) const{
    int len = w.length();

    int currentState = initialState;

    // for each symbol
    for(int i = 0; i < len; i++){
        currentState = transitionFunction->getState(currentState, w[i]);
    }

    return currentState;
}

//-----------------------------------------------------------//
//  OPERATORS
//-----------------------------------------------------------//

std::ostream& operator<<(std::ostream& os,
                                const DFA & dfa){
    os << "States#: " << dfa.getStateCount() << std::endl;
    os << "Symbol#: " << dfa.getSymbolCount() << std::endl;
    os << "Transition: " << *(dfa.getTransitionFunction());

    return os;
}