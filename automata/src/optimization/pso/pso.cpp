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
#include <particle_factory.h>
#include "pso_update_common.h"
#include "thread_pool.h"
#include "pso_common.h"

PSO::PSO(unsigned int numberOfStates, unsigned int numberOfSymbols,
         vector<int> *toolRelationResults, WordsGenerator *wordsGenerator){
    this->_numberOfStates = numberOfStates;
    this->_numberOfSymbols = numberOfSymbols;

    this->_wordsGenerator = wordsGenerator;
    this->_toolRelationResults = toolRelationResults;

    _particleDecoder = new ParticleDecoder(numberOfStates, numberOfSymbols);

    _globalBestFitness = 0;

    _loadSwarmSize();
    _generateParticles();
}


PSO::~PSO() {
    for (auto particle = _particles.begin();
         particle != _particles.end(); ++particle) {
        delete (*particle);
    }
    _particles.clear();

    delete _particleDecoder;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void PSO::compute() {
    logger::log(Verbose(PSO_V),"Particle Swarm Optimization starts");

    ConsolePlot* consolePlot = new ConsolePlot(100, 20);
    int numberOfLinesToReset = 0;

    int t = 0;
    _printInfoAndPlot(t, consolePlot, numberOfLinesToReset);
    while (!_isConverged(t++)) {
        // Calculate pbest using Fitness Function
        clk::startClock();
        this->_initFitnessFunctionParallel();
        timeMeasures.fitnessTime = clk::stopClock();

        // Update neighbourhood and compute lbest
        clk::startClock();
        pso::nbhood::updateNeighbourhoods(&(this->_particles),
                                          &(this->_particlePositions),
                                          this->_lastNumberOfClusters);
        timeMeasures.neighbouthoodTime = clk::stopClock();

        // Update particles positions
        clk::startClock();
        pso::update::updateParticles(&(this->_particles));
        timeMeasures.updateParticleTime = clk::stopClock();

        // Plot results so far
        _printInfoAndPlot(t, consolePlot, numberOfLinesToReset);
    }
    logger::log(Verbose(PSO_V), "Particle Swarm Optimization ends");
    delete consolePlot;
}

std::vector<Particle *> PSO::getBestParticles() {
    return this->_bestParticles;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void PSO::_loadSwarmSize() {
    _swarmSize = (unsigned int)(_numberOfStates * _numberOfSymbols *
                          global_settings::POPULATION_FACTOR);
    if (_swarmSize < 1) {
        throw invalid_argument("swarmSize < 1");
    }
}

void PSO::_generateParticles(){
    double posIntervalMin = global_settings::ENCODING_DELTA;
    double posIntervalMax = _numberOfStates + global_settings::ENCODING_DELTA
                            - global_settings::UPPER_BOUND_ERR;

    double velIntervalMin = (double)-_numberOfStates;
    double velIntervalMax = (double)_numberOfStates;

    double maxVelocity = (((double)_numberOfStates) / 2.0 )
                         * global_settings::SPEED_FACTOR;

    maxVelocity = maxVelocity > _numberOfStates ? _numberOfStates : maxVelocity;

    unsigned int particleDimension = _numberOfStates * _numberOfSymbols;

    ParticleFactory pf;
    _particles = pf.generateUniformParticles(_swarmSize, particleDimension,
                                             posIntervalMin, posIntervalMax,
                                             velIntervalMin, velIntervalMax,
                                             maxVelocity,
                                             _particleDecoder);

    // Save particle position for faster Clustering process.
    _particlePositions.resize(_swarmSize);
    for(unsigned int i = 0; i < _swarmSize; i++){
        _particlePositions[i] = _particles[i]->getPosition();
    }
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

void PSO::_printInfoAndPlot(int t, ConsolePlot *cPlot,
                            int &totalNumberOfLinesToReset) {
    // Clean previous entry
    for (int i = 0; i < totalNumberOfLinesToReset; i++) {
        cout << "\e[A\r";
    }

    int numberOfLinesToReset = 0;
    cout << endl;
    numberOfLinesToReset++;

    cPlot->update(t - 1, _globalBestFitness);
    numberOfLinesToReset += cPlot->print();
    cout << endl;
    numberOfLinesToReset++;

    LOG_CALC("t",t );
    numberOfLinesToReset++;

    LOG_CALC("K",_lastNumberOfClusters);
    numberOfLinesToReset++;

    LOG_CALC("Swarm Size",this->_swarmSize);
    numberOfLinesToReset++;
    LOG_CALC("States Considered", _numberOfStates);
    numberOfLinesToReset++;

    LOG_CALC("Global Best Fitness",_globalBestFitness );
    numberOfLinesToReset++;

    LOG_CALC("Neighbourhood Time",timeMeasures.neighbouthoodTime );
    numberOfLinesToReset++;
    LOG_CALC("Fitness Time",timeMeasures.fitnessTime);
    numberOfLinesToReset++;
    LOG_CALC("Particle Update Time",timeMeasures.updateParticleTime);
    numberOfLinesToReset++;

    totalNumberOfLinesToReset = numberOfLinesToReset;
}

