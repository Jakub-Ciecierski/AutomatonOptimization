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

    intervalMin = global_settings::ENCODING_DELTA;
    intervalMax = numberOfStates
                  + global_settings::ENCODING_DELTA
                  - global_settings::UPPER_BOUND_ERR;

    velocity_max = ((double)numberOfStates/2) * global_settings::SPEED_FACTOR;

    std::cout << "Velocity Max: [" << velocity_max << std::endl;
    std::cout << "Interval: [" << intervalMin << ", " << intervalMax << "]" << std::endl;

    try {

        _loadAndLogRandomPosition(_length,
                                  intervalMin,
                                  intervalMax);
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

    std::cout << "Before cast: " << position << std::endl;
    std::cout << "After cast: " << utils::vectorToString(casted) << std::endl;

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

    // Don't make move bigger than velocity_max
    Point<double> potentialPosition =
            _velocity * global_settings::PARTICLE_VELOCITY
            + randomPointInSphere;

    for(int i = 0;i < potentialPosition.size(); i++){
        int sign;

        sign = 1;
        double delta = (_position[i] - potentialPosition[i]);
        if (delta < 0)
            sign = -1;

        delta *= delta;
        delta = sqrt(delta);
/*
        std::cout << "Poten: " << potentialPosition << std::endl;
        std::cout << "delta: " << delta << std::endl;
        std::cout << "Before: " << oldPosition << std::endl;
*/
        if(delta > velocity_max){
            _position[i] = _position[i] - (velocity_max*sign);
        }
        else{
            _position[i] = potentialPosition[i];
        }
    }

    _velocity = _velocity * global_settings::PARTICLE_VELOCITY + randomPointInSphere - oldPosition;

    // Check border conditions
    _checkBorderConditions(_position);

    //std::cout << "Before Position: " << oldPosition << std::endl;
    //std::cout << "After Position: " << _position << std::endl;

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


void Particle::_checkBorderConditions(Point<double>& position) {
    for(int i = 0; i < position.size(); i++) {

        if(position[i] < intervalMin) {
            position[i] = intervalMin;
            _velocity[i] = 0;
        }

        if(position[i] > intervalMax) {
            position[i] = intervalMax;
            _velocity[i] = 0;
        }

    }
}
