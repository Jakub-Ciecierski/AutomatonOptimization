//
// Created by dybisz on 11/12/15.
//

#include <random_sphere.h>
#include "particle.h"

Particle::Particle(int numberOfStates, int numberOfSymbols, double speedFactor) :
        _length(numberOfStates * numberOfSymbols),
        _numberOfStates(numberOfStates),
        _numberOfSymbols(numberOfSymbols),
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

    bestFitness = 0;

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
    _velocity = utils::generateRandomPoint((double)_position.size(), minDim, maxDim);
    LOG_CALC("_velocity", _velocity.toString());
}


void Particle::_loadAndLogMaxVelocity(int numberOfStates, double speedFactor) {
    _maxVelocity = (((double)numberOfStates) / 2.0 ) * speedFactor;

    if(_maxVelocity > numberOfStates) {
        throw invalid_argument("_maxVelocity: " + to_string(_maxVelocity) + " <= numberOfStates");
    }

    LOG_DEBUG("_maxVelocity set to:" + to_string(_maxVelocity));
}

// TODO clean up
void Particle::update() {
    Point<double> oldPosition = _position;
    Point<double> y_p1 = (pbest - oldPosition) * global_settings::LEARNING_FACTOR;
    Point<double> y_p2 = (lbest - oldPosition) * (global_settings::LEARNING_FACTOR);
    Point<double> centerOfGravity = (oldPosition + y_p1 + y_p2) / 3.0;
    Point<double> randomPointInSphere = _generateRandomPointInSphere(centerOfGravity, oldPosition);
    _position = _velocity * global_settings::PARTICLE_VELOCITY + randomPointInSphere;
    _velocity = _velocity * global_settings::PARTICLE_VELOCITY + randomPointInSphere - oldPosition;

    // Check border conditions
    _checkBorderConditions(_position);

    // Update automaton
    _loadAndLogDFA(_numberOfStates, _numberOfSymbols, _position);

}

// TODO for large n's it will be rather slow
Point<double> Particle::_generateRandomPointInSphere(Point<double> centerOfGravity, Point<double> oldPosition) {
    Point<double> randomPointWithinSphere;
    RandomSphere randomSphere(centerOfGravity, oldPosition);
    randomPointWithinSphere = randomSphere.generatePointWithin();
    return randomPointWithinSphere;
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

// TODO interval as global var
void Particle::_checkBorderConditions(Point<double>& position) {
    for(int i = 0; i < position.size(); i++) {

        if(position[i] < 1) {
            position[i] = 1;
            _velocity[i] = 0;
        }

        if(position[i] > _numberOfStates) {
            position[i] = _numberOfStates;
            _velocity[i] = 0;
        }

    }
}
