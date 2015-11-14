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
#include "words_generator.h"

class PSO {
public:
    PSO(string toolUrl, int numberOfStates, int populationFactor);

    ~PSO();

    void compute();

private:
    DFA _tool;
    vector<Particle *> _particles;
    WordsGenerator *_wordsGenerator;

    int _psoNumberOfStates;
    int _numberOfSymbols;
    int _swarmSize;
    int _populationFactor;
    vector<int> _toolFitnessResults;

    void _loadAndLogSwarmSize();

    int _calculateSwarmSize(int numberOfStates, int numberOfSymbols, int populationFactor);

    void _loadAndLogRandomParticles(int numberOfParticles);

    vector<Particle *> _generateRandomParticles(int numberOfParticles);

    void _loadAndLogWordsGenerator(vector<int> alphabet);

    void _loadAndLogToolFitnessResults();

    vector<int> _generateToolFitnessResults();

    double _fitnessFunction(Particle p);
};

#endif //AC_PSO_H
