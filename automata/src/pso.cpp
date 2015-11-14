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
        _loadAndLogWordsGenerator(_tool.alphabet);
        _loadAndLogToolFitnessResults();
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }
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
vector<Particle *> PSO::_generateRandomParticles(int numberOfParticles) {
    vector<Particle *> particles;
    double speedFactor = 0.5;

    if (numberOfParticles < 1) {
        throw invalid_argument("numberOfParticles < 1");
    }

    for (int i = 0; i < numberOfParticles; i++) {
        Particle *p = new Particle(_psoNumberOfStates, _numberOfSymbols, speedFactor);
        particles.push_back(p);
    }
    return particles;
}

void PSO::_loadAndLogWordsGenerator(vector<int> alphabet) {
    _wordsGenerator = new WordsGenerator(alphabet);
    LOG_INFO("Pairs of Words generated");
}

void PSO::_loadAndLogToolFitnessResults() {
    _toolFitnessResults = _generateToolFitnessResults();
    LOG_INFO("Fitness function results for _tool calculated and saved.");
}

vector<int> PSO::_generateToolFitnessResults() {
    vector<int> toolFitnessResults;
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();

    // TODO(dybisz) check for errors

    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair) {
        bool inRelation = _tool.checkRelationInducedByLanguage((*pair).word1, (*pair).word2);
        int result = (inRelation) ? 1 : 0;
        toolFitnessResults.push_back(result);
    }

    return toolFitnessResults;
}

double PSO::_fitnessFunction(Particle *p) {
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();
    double count = 0;

    for (int i = 0; i < pairs.size(); i++) {
        Word w1 = pairs[i].word1;
        Word w2 = pairs[i].word2;
        bool inRelation = p->_particleRepresentation->checkRelationInducedByLanguage(w1, w2);
        int result = (inRelation) ? 1 : 0;
        count += (result == _toolFitnessResults[i]) ? 1 : 0;
    }

    return count / (double) pairs.size();
}

void PSO::compute() {
    LOG_INFO("Particle Swarm Optimization: start computing...")
    for (int t = 0; t < MAX_ITER; t++) {

        LOG_INFO("Interation: " + to_string(t));

        // Calculate pbest using Fitness Function
        _pbestp = _calculatePBest(_particles);

        LOG_CALC("_pbestp",_pbestp.toString())
        LOG_CALC("fitness:", to_string(_bestFitnessTracking));

        // Calculate lbest using K-Means and MCFiut
        _lbestp = _pbestp;
        LOG_CALC("_lbestp",_lbestp.toString())

        // Update particles positions
        _updateParticles(_pbestp, _lbestp);

    }
    LOG_INFO("Particle Swarm Optimization: scomputing ends.")
}

Point<double> PSO::_calculatePBest(vector<Particle *> particles) {
    Point<double> pbestp;
    double bestFitness = -1;

    for (int i = 0; i < particles.size(); i++) {
        double fitness = _fitnessFunction(particles[i]);

        if (fitness > bestFitness) {
            pbestp = particles[i]->_position;
            bestFitness = fitness;
        }

    }
    _bestFitnessTracking = bestFitness;

    return pbestp;
}

void PSO::_updateParticles(Point<double> pbestp, Point<double> lbestp) {
    for (auto particle : _particles) {
        particle->update(pbestp, lbestp);
    }
}

PSO::~PSO() {
    for (auto particle = _particles.begin(); particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();

    delete _wordsGenerator;
}



