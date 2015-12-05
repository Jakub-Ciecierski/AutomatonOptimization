//
// Created by dybisz on 11/12/15.
//

#include <random_sphere.h>
#include <logger.h>
#include "particle.h"

Particle::Particle(unsigned int numberOfStates, unsigned int numberOfSymbols) :
        _numberOfSymbols(numberOfSymbols),
        _numberOfStates(numberOfStates){
    _length = _numberOfSymbols * _numberOfStates;

    // Must be called before other _loads :(
    _loadInterval();

    try {
        _loadAndLogRandomPosition(_length,
                                  _intervalMin,
                                  _intervalMax);
        _loadAndLogRandomVelocity(-numberOfStates, numberOfStates);
        _loadAndLogMaxVelocity(numberOfStates);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }

    this->updateDFA();

    this->_fitness = 0;

    this->saveCurrentConfigAsBest();
}

Particle::Particle(const Particle& p) :
        _numberOfSymbols(p._numberOfSymbols),
        _numberOfStates(p._numberOfStates) {
    _length = _numberOfSymbols * _numberOfStates;

    _bestFitness = p._bestFitness;
    _fitness = p._fitness;

    _pbest = p._pbest;
    _lbest = p._lbest;

    _pbestDFA = new DFA(*(p.getBestDFA()));
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

void Particle::_loadAndLogRandomPosition(int length, double minDim, double maxDim) {
    _position = _generateRandomPosition(length, minDim, maxDim);
    //LOG_CALC("_position", "[" + _positionToString() + "]");
}

Point<double> Particle::_generateRandomPosition(int length, double minDim, double maxDim) {
    Point<double> position;

    for (int i = 0; i < length; i++) {
        double randomDouble = utils::generateRandomNumber(minDim, maxDim);
        position.addDimension(randomDouble);
    }

    return position;
}

void Particle::_loadAndLogRandomVelocity(double minDim, double maxDim) {
    _velocity = utils::generateRandomPoint((double)_position.size(), minDim, maxDim);
    //LOG_CALC("_velocity", _velocity.toString());
}

void Particle::_loadAndLogMaxVelocity(int numberOfStates) {
    _maxVelocity = (((double)numberOfStates) / 2.0 )
                    * global_settings::SPEED_FACTOR;

    if(_maxVelocity > numberOfStates) {
        throw invalid_argument("This must be true: _maxVelocity: "
                               + to_string(_maxVelocity)
                               + " <= numberOfStates");
    }

    LOG_DEBUG("_maxVelocity set to:" + to_string(_maxVelocity));
}

void Particle::_loadInterval(){
    _intervalMin = global_settings::ENCODING_DELTA;
    _intervalMax = _numberOfStates + global_settings::ENCODING_DELTA
                   - global_settings::UPPER_BOUND_ERR;
}

// ----------------------------------------------------------------------------