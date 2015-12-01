//
// Created by dybisz on 11/12/15.
//

#include <random_sphere.h>
#include "particle.h"

Particle::Particle(int numberOfStates, int numberOfSymbols) :
        _numberOfSymbols(numberOfSymbols),
        _numberOfStates(numberOfStates){
    //LOG_INFO("Creating new particle...");

    _length = _numberOfSymbols * _numberOfStates;

    // Must be called before other _loads :(
    _loadInterval();

    try {
        _loadAndLogRandomPosition(_length,
                                  _intervalMin,
                                  _intervalMax);
        _loadAndLogDFA(numberOfStates, numberOfSymbols, _position);
        _loadAndLogRandomVelocity(-numberOfStates, numberOfStates);
        _loadAndLogMaxVelocity(numberOfStates);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }

    bestFitness = 0;
    fitness = 0;

    //LOG_INFO("Following particle was created: ..."); // TODO(dybisz) change
}

Particle::Particle(const Particle& p) :
        _numberOfSymbols(p._numberOfSymbols),
        _numberOfStates(p._numberOfStates) {
    _length = _numberOfSymbols * _numberOfStates;

    bestFitness = p.bestFitness;
    fitness = p.fitness;

    pbest = p.pbest;
    lbest = p.lbest;
}

Particle::~Particle() {
    delete _particleRepresentation;

    delete resultPack.dfa;
}

void Particle::updateDFARepresentation(){
    vector<int> roundedPosition = _castFromPositionToDFA(_position);
    _particleRepresentation = new DFA(_numberOfStates, _numberOfSymbols,
                                      roundedPosition);
}

ResultPack Particle::getResultPack(){
    if (resultPack.dfa == NULL)
        resultPack.dfa = new DFA(this->_numberOfStates,
                          this->_numberOfSymbols,
                          this->_castFromPositionToDFA(this->pbest));

    resultPack.position = &(this->pbest);
    resultPack.fitness = &(this->bestFitness);

    return resultPack;
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

void Particle::_loadAndLogDFA(int numberOfStates, int numberOfSymbols, Point<double> position) {
    vector<int> roundedPosition = _castFromPositionToDFA(position);
    _particleRepresentation = new DFA(numberOfStates, numberOfSymbols,
                                      roundedPosition);
}

/*
 * Encodes position to automaton.
 */
vector<int> Particle::_castFromPositionToDFA(Point<double> position) {

    vector<int> casted;
    for (int i = 0; i < position.size(); i++) {
        int encodedValue;
        double delta;

        encodedValue = (int)position[i];
        delta = position[i] - encodedValue;
        if (delta >= global_settings::ENCODING_DELTA)
            encodedValue++;

        casted.push_back(encodedValue);
    }

    return casted;
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

string Particle::_positionToString() {
    string stringOut = "";
    for (int i = 0; i < _position.size(); i++) {
        stringOut += (to_string(_position[i]) + " ");
    }
    return stringOut;
}
