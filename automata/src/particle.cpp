//
// Created by dybisz on 11/12/15.
//

#include "particle.h"

Particle::Particle(int numberOfStates, int numberOfSymbols, double speedFactor) :
        _length(numberOfStates * numberOfSymbols),
        _speedFactor(speedFactor){
    LOG_INFO("Creating new particle...");
    try {

        _loadAndLogRandomPosition(_length, 1, numberOfStates);
        _loadAndLogDFA(numberOfStates, numberOfSymbols, _position);
        _loadAndLogRandomVelocity(-numberOfStates, numberOfStates);
        _loadAndLogMaxVelocity(numberOfStates, _speedFactor);

    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
    LOG_INFO("Following particle was created: ..."); // TODO(dybisz) change to  neat summary
}

void Particle::_loadAndLogRandomPosition(int length, double minDim, double maxDim) {
    _position = _generateRandomPosition(length, minDim, maxDim);
    LOG_DEBUG("Particle' position created: " + _positionToString());
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
    _particleRepresentation = new DFA(numberOfStates, numberOfSymbols, roundedPosition);
}

// TODO(dybisz) KUBA CHANGE IT TO SOMETHING REASONABLE PLX
vector<int> Particle::_castFromPositionToDFA(Point<double> position) {

    vector<int> casted;
    for (int i = 0; i < position.size(); i++) {
        int val = (int) position[i];
        casted.push_back(val);
    }

    LOG_DEBUG("_position casted to: " + utils::vectorToString(casted));

    return casted;
}

void Particle::_loadAndLogRandomVelocity(double minDim, double maxDim) {
    _velocity = utils::generateRandomNumber(minDim, maxDim);
    LOG_DEBUG("_velocity randomized:" + to_string(_velocity));
}


void Particle::_loadAndLogMaxVelocity(int numberOfStates, double speedFactor) {
    _maxVelocity = (((double)numberOfStates) / 2.0 ) * speedFactor;

    if(_maxVelocity > numberOfStates) {
        throw invalid_argument("_maxVelocity: " + to_string(_maxVelocity) + " <= numberOfStates");
    }

    LOG_DEBUG("_maxVelocity set to:" + to_string(_maxVelocity));
}

string Particle::_positionToString() {
    string stringOut = "";
    for (int i = 0; i < _position.size(); i++) {
        stringOut += (to_string(_position[i]) + " ");
    }
    return stringOut;
}

Particle::~Particle() {
    delete _particleRepresentation;
}

