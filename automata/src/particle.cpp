//
// Created by dybisz on 11/12/15.
//

#include "particle.h"

Particle::Particle(int length, int minDim, int maxDim, int numberOfStates, int numberOfSymbols) :
        _length(length) {
    LOG_INFO("Creating new particle...")
    _loadAndLogRandomPosition(length, minDim, maxDim);
    _loadAndLogDFA(numberOfStates, numberOfSymbols, _position);
    _loadAndLogRandomVelocity((double)-maxDim, (double)maxDim);
    LOG_INFO("Following particle created: ...")
}

void Particle::_loadAndLogDFA(int numberOfStates, int numberOfSymbols, Point<double> position) {
    vector<int> roundedPosition = _castFromPositionToDFA(position);
    _particleRepresentation = new DFA(numberOfStates, numberOfSymbols, roundedPosition);
}

Particle::~Particle() {
    delete _particleRepresentation;
}

void Particle::_loadAndLogRandomPosition(int length, double minDim, double maxDim) {
    _position = _generateRandomPosition(length, minDim, maxDim);
    LOG_DEBUG("Particle' position created: " + _positionToString());
}

Point<double> Particle::_generateRandomPosition(int length, double minDim, double maxDim) {
    Point<double> position;

    for(int i = 0; i < length; i++) {
        double randomDouble = utils::generateRandomNumber(minDim, maxDim);
        position.addDimension(randomDouble);
    }

    return position;
}

string Particle::_positionToString() {
    string stringOut = "";
    for(int i = 0 ; i < _position.size(); i++) {
        stringOut += (to_string(_position[i]) + " ");
    }
    return stringOut;
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
