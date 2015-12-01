//
// Created by dybisz on 11/12/15.
//

#include "pso.h"

#include "log.h"
#include "mcclain_rao.h"
#include <algorithm>
#include <clock.h>
#include <algorithms/pso_fitness.h>
#include <algorithms/pso_neighbourhood.h>
#include "pso_update_common.h"
#include "thread_pool.h"
#include "pso_main.h"

PSO::PSO(int numberOfStates, int numberOfSymbols,
         vector<int> *toolRelationResults, WordsGenerator *wordsGenerator) :
        _psoNumberOfStates(numberOfStates),
        _numberOfSymbols(numberOfSymbols),
        _wordsGenerator(wordsGenerator),
        _toolRelationResults(toolRelationResults),
        _consolePlot(100, 20),
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

PSO::~PSO() {
    for (auto particle = _particles.begin();
         particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void PSO::compute() {
    logger::log("Particle Swarm Optimization starts");
    int t = 0;
    _infoPrint(t);
    while (!_isConverged(t++)) {
        // Calculate pbest using Fitness Function
        clk::startClock();

        _initFitnessFunctionParallel();

        timeMeasures.fitnessTime = clk::stopClock();

        // Update neighbourhood and compute lbest
        clk::startClock();
        // TODO Send position
        pso::nbhood::updateNeighbourhoods(&(this->_particles),
                                          &(this->_particlePositions),
                                          this->_lastNumberOfClusters);
        timeMeasures.neighbouthoodTime = clk::stopClock();

        // Update particles positions
        clk::startClock();
        pso::update::updateParticles(&(this->_particles));
        timeMeasures.updateParticleTime = clk::stopClock();

        // Plot results so far
        _infoPrint(t);
    }
    logger::log("Particle Swarm Optimization ends");
    _numberOfLinesToReset = 0;
}

std::vector<Particle *> PSO::results() {
    return this->_bestParticles;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void PSO::_loadAndLogSwarmSize() {
    _swarmSize = _calculateSwarmSize(_psoNumberOfStates, _numberOfSymbols);
    LOG_DEBUG("_swarmSize calculated: " + to_string(_swarmSize));
}

// TODO(dybisz) google test
int PSO::_calculateSwarmSize(int numberOfStates, int numberOfSymbols) {
    int swarmSize = (int)(numberOfStates * numberOfSymbols *
                    global_settings::POPULATION_FACTOR);

    if (swarmSize < 1) {
        throw invalid_argument("swarmSize < 1");
    }

    return swarmSize;
}

void PSO::_loadAndLogRandomParticles(int numberOfParticles) {
    utils::seed();
    _particles = _generateRandomParticles(numberOfParticles);

    // Save the pointers to positions
    int size = _particles.size();
    _particlePositions.resize(size);
    for(int i = 0; i < size; i++){
        _particlePositions[i] = &(_particles[i]->_position);
    }

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

// -----------------------------------------------------------------------------

void PSO::_initFitnessFunctionParallel(){
    // Create Thread pool
    threading::ThreadPool threadPool;

    // Create structure for thread arguments
    pso::thread_args* targs = new
        pso::thread_args[global_settings::TRUE_THREAD_COUNT];

    // Pointer to initial function
    void* (*ptr)(void*);
    ptr = &pso::fitness::initFitness;

    // Initialize the structure with data
    for(int i = 0;i < global_settings::TRUE_THREAD_COUNT; i++){
        targs[i].id = i;
        targs[i].thread_count = global_settings::TRUE_THREAD_COUNT;
        targs[i].particles = &(this->_particles);
        targs[i].bestParticles = &(this->_bestParticles);
        targs[i].globalBestFitness = &this->_globalBestFitness;

        targs[i].wordsGenerator = this->_wordsGenerator;
        targs[i].toolRelationResults = this->_toolRelationResults;

        targs[i].mutex = &threadPool.mutex;

        threadPool.createThread(ptr, (&targs[i]));
    }

    threadPool.joinAll();

    delete[] targs;
}

// -----------------------------------------------------------------------------

bool PSO::_isConverged(const int &t) {
    return (t > global_settings::MAX_ITER ||
            _globalBestFitness >= global_settings::FITNESS_TOLERANCE);
}

// -----------------------------------------------------------------------------


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

    LOG_CALC("Swarm Size",this->_swarmSize);
    numberOfLinesToReset++;
    LOG_CALC("States Considered",_psoNumberOfStates );
    numberOfLinesToReset++;

    LOG_CALC("Global Best Fitness",_globalBestFitness );
    numberOfLinesToReset++;

    LOG_CALC("Neighbourhood Time",timeMeasures.neighbouthoodTime );
    numberOfLinesToReset++;
    LOG_CALC("Fitness Time",timeMeasures.fitnessTime);
    numberOfLinesToReset++;
    LOG_CALC("Particle Update Time",timeMeasures.updateParticleTime);
    numberOfLinesToReset++;

    _numberOfLinesToReset = numberOfLinesToReset;
}

