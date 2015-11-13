//
// Created by dybisz on 11/12/15.
//

#include "pso.h"

PSO::PSO(string toolUrl, int numberOfStates, int populationFactor) :
        _tool(toolUrl),
        _psoNumberOfStates(numberOfStates),
        _numberOfSymbols(_tool.alphabet.size()),
        _populationFactor(populationFactor) {

    try {
        _loadAndLogSwarmSize();
        _loadAndLogRandomParticles(_swarmSize);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
}

PSO::~PSO() {
    for (auto particle = _particles.begin(); particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();
}

void PSO::_loadAndLogSwarmSize() {
    _swarmSize = _calculateSwarmSize(_psoNumberOfStates, _numberOfSymbols, _populationFactor);
    LOG_DEBUG("_swarmSize calculated: " + to_string(_swarmSize));
}

// TODO(dybisz) google test
int PSO::_calculateSwarmSize(int numberOfStates, int numberOfSymbols, int populationFactor) {
    int swarmSize = numberOfStates * numberOfSymbols * populationFactor;

    if (swarmSize < 1) {
        throw invalid_argument("swarmSize < 1");
    }

    return swarmSize;
}

void PSO::_loadAndLogRandomParticles(int numberOfParticles) {
    utils::seed();
    _particles = _generateRandomParticles(numberOfParticles);
    LOG_DEBUG(to_string(numberOfParticles) + " particles randomly generated and saved to _particles");
}

// TODO(dybisz) google test
vector<Particle*> PSO::_generateRandomParticles(int numberOfParticles) {
    vector<Particle*> particles;
    int particleLength = _psoNumberOfStates * _numberOfSymbols;

    if (numberOfParticles < 1) {
        throw invalid_argument("numberOfParticles < 1");
    }

    for(int i = 0; i < numberOfParticles; i++ ) {
        Particle* p = new Particle(particleLength, 1, _psoNumberOfStates, _psoNumberOfStates, _numberOfSymbols);
        particles.push_back(p);
    }
    return particles;
}