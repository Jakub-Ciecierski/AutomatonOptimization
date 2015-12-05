//
// Created by dybisz on 11/12/15.
//

#include <random_sphere.h>
#include <logger.h>
#include "particle.h"

Particle::Particle(unsigned int numberOfStates, unsigned int numberOfSymbols,
                    double intervalMin, double intervalMax,
                    double maxVelocity,
                    Point<double> position, Point<double> velocity) {
    this->_numberOfSymbols = numberOfSymbols;
    this->_numberOfStates = numberOfStates;
    this->_length = _numberOfSymbols * _numberOfStates;

    this->_intervalMin = intervalMin;
    this->_intervalMax = intervalMax;
    this->_maxVelocity = maxVelocity;

    this->_position = position;
    this->_velocity = velocity;

    this->_fitness = 0;

    this->updateDFA();

    this->saveCurrentConfigAsBest();
}

Particle::Particle(const Particle& p) {
    this->_numberOfSymbols = p._numberOfSymbols;
    this->_numberOfStates = p._numberOfStates;
    this->_length = _numberOfSymbols * _numberOfStates;

    this->_currentDFA = new DFA(*(p._currentDFA));
    this->_pbestDFA = new DFA(*(p.getBestDFA()));

    this->_position = p._position;
    this->_velocity = p._velocity;

    this->_bestFitness = p._bestFitness;
    this->_fitness = p._fitness;

    this->_pbest = p._pbest;
    this->_lbest = p._lbest;

    this->_maxVelocity = p._maxVelocity;

    this->_intervalMax = p._intervalMax;
    this->_intervalMin = p._intervalMin;
}

Particle::~Particle() {
    delete _currentDFA;
    delete _pbestDFA;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Particle::updateDFA(){
    TransitionFunction tf = this->_decodeToTransitionFunction();

    delete _currentDFA;
    _currentDFA = new DFA(tf);
}

void Particle::saveCurrentConfigAsBest(){
    this->_bestFitness = this->_fitness;
    this->_pbest = this->_position;

    delete this->_pbestDFA;
    this->_pbestDFA = new DFA(*(this->_currentDFA));
}

//-----------------------------------------------------------//
//  GETTERS
//-----------------------------------------------------------//

const DFA * Particle::getCurrentDFA() const{
    return this->_currentDFA;
}

const DFA * Particle::getBestDFA() const{
    return this->_pbestDFA;
}

const double& Particle::getFitness() const{
    return this->_fitness;
}

const double& Particle::getBestFitness() const{
    return this->_bestFitness;
}

const Point<double>* Particle::getPosition() const{
    return &(this->_position);
}

const Point<double>* Particle::getVelocity() const{
    return &(this->_velocity);
}

const double& Particle::getMaxVelocity() const{
    return this->_maxVelocity;
}

const Point<double>* Particle::getPBest() const{
    return &(this->_pbest);
}

const Point<double>* Particle::getLBest() const{
    return &(this->_lbest);
}

const double& Particle::getIntervalMin() const{
    return this->_intervalMin;
}
const double& Particle::getIntervalMax() const{
    return this->_intervalMax;
}

//-----------------------------------------------------------//
//  SETTERS
//-----------------------------------------------------------//

void Particle::setFitness(double fitness){
    this->_fitness = fitness;
}

void Particle::setPosition(Point<double> pos){
    this->_position = pos;
}

void Particle::setPositionDim(double value, int dim){
    if(dim < 0 || dim >= this->_position.size()){
        throw std::invalid_argument("Particle::setVelocityDimension");
    }
    this->_position[dim] = value;
}

void Particle::setVelocity(Point<double> vel){
    this->_velocity = vel;
}

void Particle::setVelocityDim(double value, int dim){
    if(dim < 0 || dim >= this->_velocity.size()){
        throw std::invalid_argument("Particle::setVelocityDimension");
    }
    this->_velocity[dim] = value;
}

void Particle::setLBest(Point<double> lbest){
    this->_lbest = lbest;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

TransitionFunction Particle::_decodeToTransitionFunction(){
    int size = this->_position.size();
    vector<int> decodedParticle(size);

    for (int i = 0; i < size; i++) {
        int encodedValue;
        double delta;

        encodedValue = (int)this->_position[i];
        delta = this->_position[i] - encodedValue;
        if (delta >= global_settings::ENCODING_DELTA)
            encodedValue++;

        // We enumerate from 0
        decodedParticle[i] = encodedValue - 1;
    }

    TransitionFunction tf(this->_numberOfStates, this->_numberOfSymbols,
                          decodedParticle);

    return tf;
}