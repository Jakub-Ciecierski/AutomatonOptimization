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
#include <geometry.h>
#include "pso_update_common.h"
#include "thread_pool.h"
#include "pso_common.h"

PSO::PSO(unsigned int numberOfStates, unsigned int numberOfSymbols,
         vector<int> *toolRelationResults, WordsGenerator *wordsGenerator){
    this->_numberOfStates = numberOfStates;
    this->_numberOfSymbols = numberOfSymbols;

    this->_wordsGenerator = wordsGenerator;
    this->_toolRelationResults = toolRelationResults;

    _particleDecoder = new ParticleDecoder(numberOfStates, numberOfSymbols,
                            global_settings::ENCODING_DELTA);

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
    _lastNumberOfClusters = 0;

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
    _swarmSize = (unsigned int)(global_settings::SWARM_SIZE);
    if (_swarmSize <= 1) {
        throw invalid_argument("swarmSize <= 1");
    }
}

void PSO::_generateParticles(){
    double posIntervalMin = global_settings::ENCODING_DELTA;
    double posIntervalMax = _numberOfStates + global_settings::ENCODING_DELTA
                            - global_settings::UPPER_BOUND_ERR;

    double velIntervalMin = (double)-_numberOfStates;
    double velIntervalMax = (double)_numberOfStates;

    double maxVelocity = global_settings::MAX_VELOCITY;

    maxVelocity = maxVelocity > _numberOfStates ? _numberOfStates : maxVelocity;

    unsigned int particleDimension = _numberOfStates * _numberOfSymbols;

    std::stringstream ss;
    ss << "Creating Particles" << std::endl;
    ss << "Particle Position Interval: "
        << "[" << posIntervalMin << ", " << posIntervalMax << "]" << std::endl;
    ss << "Max Velocity: " << maxVelocity;

    logger::log(Verbose(PSO_V), ss.str());

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

    //cPlot->update(t - 1, _globalBestFitness);
    //numberOfLinesToReset += cPlot->print();
    cout << endl;
    numberOfLinesToReset++;

    LOG_CALC("Iteration     ",t );
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;


    LOG_CALC("Swarm Size    ",this->_swarmSize);
    numberOfLinesToReset++;
    LOG_CALC("States        ", _numberOfStates);
    numberOfLinesToReset++;
    LOG_CALC("Symbols       ", _numberOfSymbols);
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    LOG_CALC("Clusters      ",_lastNumberOfClusters);
    numberOfLinesToReset++;
    LOG_CALC("GBest Fitness ",_globalBestFitness );
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    LOG_CALC("Fitness Time  ",timeMeasures.fitnessTime);
    numberOfLinesToReset++;
    LOG_CALC("Neighb Time   ",timeMeasures.neighbouthoodTime );
    numberOfLinesToReset++;
    LOG_CALC("Update Time   ",timeMeasures.updateParticleTime);
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;
    totalNumberOfLinesToReset = numberOfLinesToReset;

    /*
    if(t > 0) {
        for (unsigned int i = 0; i < _particles.size(); i++) */
/*
            Particle *bestParticle = _bestParticles[0];

            const Point<double> *currPos = (_particles[i]->getPosition());
            const Point<double> *gbestPos = bestParticle->getPBest();

            double distance = math::euclideanDistance(*currPos, *gbestPos);

            std::string str =
                    "P[" + std::to_string(i) + "] - Fitness";
            LOG_CALC(str.c_str(), _particles[i]->getFitness());
*/
/*
            Particle *bestParticle = _bestParticles[0];

            const Point<double> *currPos = (_particles[i]->getPosition());
            const Point<double> *gbestPos = bestParticle->getPBest();

            double distance = math::euclideanDistance(*currPos, *gbestPos);

            std::string str =
                    "P[" + std::to_string(i) + "] - Distance To gbest";
            LOG_CALC(str.c_str(), distance);
*/

/*
            Point<double> currPos = *(_particles[i]->getPosition());
            Point<double> oldPos = _particles[i]->oldPosition;
            //std::cout << currPos.size() << " : " << oldPos.size() << std::endl;
            double distance = math::euclideanDistance(
                                    *(_particles[i]->getPosition()),
                                    _particles[i]->oldPosition);

            std::string str = "P[" + std::to_string(i) + "] - Delta Pos Distance";
            LOG_CALC(str.c_str(), distance);
            */


}