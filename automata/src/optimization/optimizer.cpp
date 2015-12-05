//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"
#include <set>
#include <relation_induced.h>

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Optimizer::Optimizer(DFA * tool){
    _wordsGenerator = NULL;
    bestResult = NULL;
    tool_t = tool;
}


Optimizer::~Optimizer() {
    delete _wordsGenerator;
    delete bestResult;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Optimizer::start() {
    // 1) Generate sample set of words
    generateWords();

    std::cout << "Computing Relation" << std::endl;
    // 2) Compute the relation R-L and save the results
    computeRelation();

    std::cout << "Starting PSO logic" << std::endl;
    int r = tool_t->getSymbolCount();
    // 3) Run PSO instances
    for (int s = global_settings::MIN_STATES;
            s <= global_settings::MAX_STATES; s++) {
        if (runPSO(s, r))
            break;
    }

    // 4) Run test set
    computeTestSetResults();
    std::cout << "after test set results\n";
}

Particle* Optimizer::getResult() {
    return this->bestResult;
}

const DFA * Optimizer::getTool() const{
    return this->tool_t;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Optimizer::generateWords() {
    std::vector<int>* alphabet = tool_t->getAlphabet();

    _wordsGenerator = new WordsGenerator(*alphabet);
}

void Optimizer::computeRelation() {
    vector<PairOfWords> *pairs = _wordsGenerator->getPairs();

    // TODO(dybisz) check for errors

    for (auto pair = pairs->begin(); pair != pairs->end(); ++pair) {
        bool inRelation = automata::isInRelationInduced(*tool_t,
                                                        (*pair).word1,
                                                        (*pair).word2);

        int result = (inRelation) ? 1 : 0;
        _toolRelationResults.push_back(result);
    }
}


void Optimizer::computeTestSetResults() {
    cout << "COMPUTING TEST SET\n";
    vector<PairOfWords> *pairs = _wordsGenerator->getTestPairs();
    int count = 0;
    unsigned int pairsSize = pairs->size();
    double result = -1;

    const DFA * dfaResult = bestResult->getBestDFA();

    for (unsigned int i = 0; i < pairsSize; i++) {
        PairOfWords* pair = &((*pairs)[i]);

        const Word& w1 = pair->word1;
        const Word& w2 = pair->word2;

        bool inRelationTool = automata::isInRelationInduced(*tool_t, w1, w2);

        bool inRelationTest = automata::isInRelationInduced(*dfaResult, w1, w2);

        count += (inRelationTest && inRelationTool) ? 1 : 0;
    }

    result = count / (double) pairsSize;
    cout << "TEST SET RESULT: " << result << endl;
}

bool Optimizer::runPSO(int s, int r) {
    bool returnValue = false;

    pso = new PSO(s, r, &_toolRelationResults, _wordsGenerator);
    pso->compute();

    std::vector<Particle *> psoResults = pso->results();

    // Find the result with minimum state usage
    Particle *bestPSOResult = selectParticleUsingMinimumStates(psoResults);
    compareResultWithBestResult(bestPSOResult);

    // If it is what we are looking for, stop.
    if (this->bestResult->getBestFitness() >=
                global_settings::FITNESS_TOLERANCE) {
        returnValue = true;
    }

    delete pso;

    return returnValue;
}

Particle *Optimizer::selectParticleUsingMinimumStates(
        std::vector<Particle *> results) {
    std::vector<std::set<int>> stateCountVec;

    vector<PairOfWords> *pairs = _wordsGenerator->getPairs();
    // For each result check how many states it uses.
    for (unsigned int i = 0; i < results.size(); i++) {
        Particle *result = results[i];
        std::set<int> s;

        const DFA * dfa = result->getBestDFA();

        for (auto pair = pairs->begin(); pair != pairs->end(); ++pair) {
            int state;

            state = dfa->compute((*pair).word1);
            s.insert(state);
            state = dfa->compute((*pair).word2);
            s.insert(state);
        }
        stateCountVec.push_back(s);
    }

    int minIndex = 0;
    unsigned int minCount = stateCountVec[minIndex].size();
    for (unsigned int i = 0; i < stateCountVec.size(); i++) {
        if (minCount > stateCountVec[i].size()) {
            minIndex = i;
            minCount = stateCountVec[i].size();
        }
    }

    return results[minIndex];
}

void Optimizer::compareResultWithBestResult(Particle *particle) {
    // Check if it is better than previous
    if (this->bestResult == NULL) {
        this->bestResult = new Particle(*particle);
    }
    else if (this->bestResult->getBestFitness() < particle->getBestFitness()) {
        delete this->bestResult;
        this->bestResult = new Particle(*particle);
    }
}

