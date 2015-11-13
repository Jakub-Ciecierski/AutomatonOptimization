//
// Created by dybisz on 11/12/15.
//

#ifndef AC_PSO_H
#define AC_PSO_H

#include <vector>
#include <string>
#include <stdexcept>
#include "dfa.h"
#include "particle.h"

class PSO {
public:
    PSO(string toolUrl, int numberOfStates, int populationFactor);
    ~PSO();
private:
    DFA _tool;
    int _psoNumberOfStates;
    int _numberOfSymbols;
    int _swarmSize;
    int _populationFactor;
    vector<Particle*> _particles;
    void _loadAndLogSwarmSize();
    int _calculateSwarmSize(int numberOfStates, int numberOfSymbols, int populationFactor);
    void _loadAndLogRandomParticles(int numberOfParticles);
    vector<Particle*> _generateRandomParticles(int numberOfParticles);
};

#endif //AC_PSO_H
