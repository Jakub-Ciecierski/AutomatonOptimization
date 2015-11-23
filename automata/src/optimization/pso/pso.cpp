//
// Created by dybisz on 11/12/15.
//

#include "pso.h"
#include "mcclain_rao.h"
#include <algorithm>
#include "log.h"

PSO::PSO(int numberOfStates, int numberOfSymbols,
         vector<int> *toolRelationResults, WordsGenerator *wordsGenerator) :
        _wordsGenerator(wordsGenerator),
        _consolePlot(100, 20),
        _psoNumberOfStates(numberOfStates),
        _numberOfSymbols(numberOfSymbols),
        _toolRelationResults(toolRelationResults),
        _numberOfLinesToReset(0) {
    try {
        _loadAndLogSwarmSize();
        _loadAndLogRandomParticles(_swarmSize);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }

    _globalBestFitness = 0;
}

void PSO::_loadAndLogSwarmSize() {
    _swarmSize = _calculateSwarmSize(_psoNumberOfStates, _numberOfSymbols);
    LOG_DEBUG("_swarmSize calculated: " + to_string(_swarmSize));
}

// TODO(dybisz) google test
int PSO::_calculateSwarmSize(int numberOfStates, int numberOfSymbols) {
    int swarmSize = numberOfStates * numberOfSymbols *
                    global_settings::POPULATION_FACTOR;

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

    if (numberOfParticles < 1) {
        throw invalid_argument("numberOfParticles < 1");
    }

    for (int i = 0; i < numberOfParticles; i++) {
        Particle *p = new Particle(_psoNumberOfStates, _numberOfSymbols);
        particles.push_back(p);
    }
    return particles;
}

double PSO::_fitnessFunction(Particle *p) {
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();
    double count = 0;

    for (unsigned int i = 0; i < pairs.size(); i++) {
        Word w1 = pairs[i].word1;
        Word w2 = pairs[i].word2;
//        cout << "CALC DIRaaaaaaaaaaaaaa1\n";
        // HAHA MAM XD
        bool inRelation = p->_particleRepresentation->checkRelationInducedByLanguage(w1, w2);
//        int pState = p->_particleRepresentation->compute()

//        cout << "CALC DIRaaaaaaaaaaaaaa2\n";
        int result = (inRelation) ? 1 : 0;
        count += (result == (*_toolRelationResults)[i]) ? 1 : 0;
    }

    return count / (double) pairs.size();
}

void PSO::compute() {
    LOG_INFO("Particle Swarm Optimization: start computing...")
    int t = 0;
    while (!isConverged(t++)) {
//        LOG_INFO("Interation: " + to_string(t));
//        cout << "aaaaaaaaaaaaaaaaaa0\n";
        // Calculate pbest using Fitness Function
        _calculatePBestAndFitness(_particles);
//        cout << "aaaaaaaaaaaaaaaaaaaaaaaaaa1\n";
        // Update neighbourhood and compute lbest
        _updateNeighbourhoods();
//        cout << "aaaaaaaaaaaaaaaaaaaa2\n";
        // Update particles positions
        _updateParticles();
//        cout << "aaaaaaaaaaaaaaaaaaaaaa3\n";
        // Plot results so far
        _infoPrint(t);
    }
    LOG_INFO("Particle Swarm Optimization: scomputing ends.")
    _numberOfLinesToReset = 0;
}

std::vector<Particle *> PSO::results() {
    return this->_bestParticles;
}

void PSO::_calculatePBestAndFitness(vector<Particle *> particles) {

    for (unsigned int i = 0; i < particles.size(); i++) {

        double prevFitness = particles[i]->fitness;
        particles[i]->fitness = _fitnessFunction(particles[i]);

        double delta = particles[i]->fitness - prevFitness;

        // Check if particle is in new pbest
        if (particles[i]->bestFitness < particles[i]->fitness) {
            particles[i]->pbest = particles[i]->_position;
            particles[i]->bestFitness = particles[i]->fitness;
        }
        // Update global best fitness value
        _calculateGBestFitness(particles[i]);

    }
}

void PSO::_updateParticles() {
    for (auto particle : _particles) {
        particle->update();
    }
}

void PSO::_calculateGBestFitness(Particle *particle) {
    // Check if another particle has global fitness
    if (_globalBestFitness == particle->fitness) {
        // If that particle is not already here
        if (std::find(_bestParticles.begin(), _bestParticles.end(),
                      particle) == _bestParticles.end()) {
            _bestParticles.push_back(particle);
        }
    }

    else if (_globalBestFitness < particle->fitness) {
        _bestParticles.clear();

        _globalBestFitness = particle->fitness;

        _bestParticles.push_back(particle);
    }
}

/*
 * Updates the neighbourhood.
 */
void PSO::_updateNeighbourhoods() {
    // Compute cluster evaluation.
    McClainRao<double> mc_r(global_settings::START_K,
                            global_settings::END_K);

    // Get vector of points from vector of particles.
    // Must preserve the indexing !!!
    vector<Point<double> *> points = _particlesToPoints(_particles);

    mc_r.compute(&points);

    // Get the most optimal clustering
    KMeans<double> *km = mc_r.getBestClustering();
    _lastNumberOfClusters = km->getK();
    // For each neighbourhood (cluster), find the lbest
    for (int c = 0; c < km->getK(); c++) {
        std::vector<int> clusterIndices = km->getClusterIndices(c);

        int bestIndex = clusterIndices[0];
        double bestFitness = _particles[bestIndex]->bestFitness;

        // Find lbest
        for (unsigned int i = 0; i < clusterIndices.size(); i++) {
            int index = clusterIndices[i];

            if (bestFitness < _particles[index]->bestFitness) {
                bestFitness = _particles[index]->bestFitness;
                bestIndex = index;
            }
        }

        // Assign lbest to each particle
        for (unsigned int i = 0; i < clusterIndices.size(); i++) {
            int index = clusterIndices[i];
            _particles[index]->lbest = _particles[bestIndex]->_position;
        }
    }
}

vector<Point<double> *> PSO::_particlesToPoints(vector<Particle *> particles) {
    unsigned int size = particles.size();
    vector<Point<double> *> points(size);

    for (unsigned int i = 0; i < size; i++) {
        points[i] = (&(particles[i]->_position));
    }

    return points;
}

bool PSO::isConverged(const int &t) {
    return (t > global_settings::MAX_ITER ||
            _globalBestFitness >= global_settings::FITNESS_TOLERANCE);
}


PSO::~PSO() {
    for (auto particle = _particles.begin(); particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();
}


void PSO::_infoPrint(int t) {

    // Clean previous entry
    for (int i = 0; i < _numberOfLinesToReset; i++) {
        cout << "\e[A\r";
    }

    int numberOfLinesToReset = 0;
    cout << endl;
    numberOfLinesToReset++;

    _consolePlot.update(t - 1, _globalBestFitness);
    numberOfLinesToReset +=_consolePlot.print();
    cout << endl;
    numberOfLinesToReset++;

    LOG_CALC("t",t );
    numberOfLinesToReset++;

    LOG_CALC("K",_lastNumberOfClusters);
    numberOfLinesToReset++;

    LOG_CALC("States Considered",_psoNumberOfStates );
    numberOfLinesToReset++;

    LOG_CALC("Global Best Fitness",_globalBestFitness );
    numberOfLinesToReset++;

    _numberOfLinesToReset = numberOfLinesToReset;
}

