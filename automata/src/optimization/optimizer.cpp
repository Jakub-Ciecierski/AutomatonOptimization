//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"
#include <set>
#include <vector>

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Optimizer::Optimizer(string toolUrl) : tool(toolUrl) {
    _wordsGenerator = NULL;
    bestResult = NULL;
}

Optimizer::~Optimizer(){
    delete _wordsGenerator;
    delete bestResult;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Optimizer::start() {
    // 1) Generate sample set of words
    generateWords();

    // 2) Compute the relation R-L and save the results
    computeRelation();

    int r = tool.alphabet.size();
    // 3) Run PSO instances
    for(int s = global_settings::MIN_STATES;
            s <= global_settings::MAX_STATES; s++){
        if(runPSO(s, r))
            break;
    }

    printResult();

}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Optimizer::generateWords() {
    LOG_INFO("Generating Pairs of Words");
    _wordsGenerator = new WordsGenerator(tool.alphabet);
    LOG_INFO("Pairs of Words generated");
}

void Optimizer::computeRelation() {
    vector<PairOfWords> pairs = _wordsGenerator->getPairs();

    // TODO(dybisz) check for errors

    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair) {
        bool inRelation = tool.checkRelationInducedByLanguage((*pair).word1,
                                                              (*pair).word2);
        int result = (inRelation) ? 1 : 0;
        _toolRelationResults.push_back(result);
    }
    LOG_INFO("Fitness function results for _tool calculated and saved.");
}

bool Optimizer::runPSO(int s, int r) {
    //logger::log(Verbose(OPTIMIZER), "Running PSO\n",
    //           "States #: ", s, " Symbols #: ", r);

    bool returnValue = false;

    pso = new PSO(s, r, &_toolRelationResults, _wordsGenerator);

    pso->compute();

    std::vector<Particle*> results = pso->results();

    int size = results.size();
    //logger::log(Verbose(OPTIMIZER), "Found ", results.size(),
    //           " results." , " Choosing best...");


    // Find the result with minimum state usage
    Particle* bestResult = selectParticleUsingMinimumStates(results);

    // Check if it is better than previous
    if(this->bestResult == NULL){
        this->bestResult = new Particle(*bestResult);
    }
    else if(this->bestResult->bestFitness < bestResult->bestFitness){
        delete this->bestResult;
        this->bestResult = new Particle(*bestResult);
    }
    // If it is what we are looking for, stop.
    if(this->bestResult->bestFitness >= global_settings::FITNESS_TOLERANCE) {
        returnValue = true;
    }

    delete pso;

    return returnValue;
}

Particle* Optimizer::selectParticleUsingMinimumStates(
        std::vector<Particle *> results){
    int size = results.size();
    std::vector<std::set<int>> stateCountVec;

    vector<PairOfWords> pairs = _wordsGenerator->getPairs();
    // For each result check how many states it uses.
    for(unsigned int i = 0;i < results.size(); i++) {
        Particle* result = results[i];
        std::set<int> s;

        DFA dfa = DFA(result->_numberOfStates,
                      result->_numberOfSymbols,
                      result->_castFromPositionToDFA(result->pbest));

        for (auto pair = pairs.begin(); pair != pairs.end(); ++pair){
            int state;

            state = dfa.compute((*pair).word1);
            s.insert(state);
            state = dfa.compute((*pair).word2);
            s.insert(state);
        }
        stateCountVec.push_back(s);
    }

    int minIndex = 0;
    int minCount = stateCountVec[minIndex].size();
    for(unsigned int i = 0; i < stateCountVec.size(); i++){
        if(minCount > stateCountVec[i].size()){
            minIndex = i;
            minCount = stateCountVec[i].size();
        }
    }

    return results[minIndex];
}

void Optimizer::printResult(){
    std::cout << "Best result: \n"
    << "[position]: " << this->bestResult->pbest
    << "\n[fitness]: " << this->bestResult->bestFitness << std::endl;
}