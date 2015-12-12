//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"

#include <set>
#include <drawer.h>
#include <sys/stat.h>
#include <error.h>

#include "relation_induced.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Optimizer::Optimizer(DFA * tool){
    _wordsGenerator = NULL;
    bestParticle = NULL;
    this->tool = tool;
}


Optimizer::~Optimizer() {
    delete _wordsGenerator;
    delete bestParticle;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Optimizer::start() {
    summarizeTool(tool);

    // 1) Generate sample set of words
    generateWords();

    // 2) Compute the relation R-L and save the results
    computeRelation();

    int r = tool->getSymbolCount();
    // 3) Run PSO instances
    for (int s = global_settings::MIN_STATES;
            s <= global_settings::MAX_STATES; s++) {
        runPSOLogic(s, r);
    }

    summarizeBestPSOResult();
}

const Particle* Optimizer::getBestParticle() const{
    return this->bestParticle;
}

const DFA* Optimizer::getTool() const{
    return this->tool;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Optimizer::generateWords() {
    logger::log(Verbose(OPTIMIZER_V), "Generating Words");

    std::vector<int>* alphabet = tool->getAlphabet();

    _wordsGenerator = new WordsGenerator(*alphabet);
}

void Optimizer::computeRelation() {
    logger::log(Verbose(OPTIMIZER_V), "Computing Relation");

    vector<PairOfWords> *pairs = _wordsGenerator->getPairs();

    // TODO(dybisz) check for errors

    for (auto pair = pairs->begin(); pair != pairs->end(); ++pair) {
        bool inRelation = automata::isInRelationInduced(*tool,
                                                        (*pair).word1,
                                                        (*pair).word2);

        int result = (inRelation) ? 1 : 0;
        _toolRelationResults.push_back(result);
    }
}

double Optimizer::computeTestSetResults(Particle* particle) {
    vector<PairOfWords> *pairs = _wordsGenerator->getTestPairs();
    int count = 0;
    unsigned int pairsSize = pairs->size();
    double result = -1;

    const DFA * dfaResult = particle->getBestDFA();

    for (unsigned int i = 0; i < pairsSize; i++) {
        PairOfWords* pair = &((*pairs)[i]);

        const Word& w1 = pair->word1;
        const Word& w2 = pair->word2;

        bool inRelationTool = automata::isInRelationInduced(*tool, w1, w2);

        bool inRelationTest = automata::isInRelationInduced(*dfaResult, w1, w2);

        count += (inRelationTest && inRelationTool) ? 1 : 0;
    }

    result = count / (double) pairsSize;

    return result;
}

void Optimizer::runPSOLogic(int s, int r) {
    std::stringstream ss;
    ss << "Starting PSO" << std::endl;
    ss << "States:  " << s << std::endl;
    ss << "Symbols: " << r;
    logger::log(Verbose(OPTIMIZER_V), ss.str());

    pso = new PSO(s, r, &_toolRelationResults, _wordsGenerator);
    pso->compute();

    std::vector<Particle *> psoResults = pso->getBestParticles();

    // Find the result with minimum state usage
    Particle* bestPSOResult = selectParticleUsingMinimumStates(psoResults);
    double testSetResult = computeTestSetResults(bestPSOResult);
    compareResultWithBestResult(bestPSOResult, testSetResult);

    std::string info = "PSO Result Summary - States = " + std::to_string(s);
    summarize(bestPSOResult, testSetResult, s, info);

    delete pso;

}

Particle *Optimizer::selectParticleUsingMinimumStates(
        const std::vector<Particle *>& results) {
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


void Optimizer::compareResultWithBestResult(Particle *particle,
                                            double testSetResult) {
    // Check if it is better than previous
    if (this->bestParticle == NULL) {
        this->bestParticle = new Particle(*particle);
    }
    else if (bestTestingSetResult < testSetResult){
        delete this->bestParticle;
        this->bestParticle = new Particle(*particle);

        bestTestingSetResult = testSetResult;
    }
}

void Optimizer::summarize(Particle* particle,
                            double testSetResult, int psoStateCount,
                            std::string headerInfo){
    std::string dirpath = logger::settings::FULL_DIR_STR;

    const DFA* dfa = particle->getBestDFA();

    // Build string for result
    stringstream ss;

    ss << headerInfo << std::endl;
    ss << *dfa << std::endl;
    ss << "Fitness:  " << particle->getBestFitness() << std::endl;
    ss << "Test Set: " << testSetResult;

    std::string resultDirpath = dirpath + "/" +
            "pso_s" + std::to_string(psoStateCount);

    if (mkdir(resultDirpath.c_str(), 0777) < 0)
        if (errno !=EEXIST) ERR("mkdir");

    std::string resultFileName =
            resultDirpath + "/" +
                    "dfa_result_pso_s" +  std::to_string(psoStateCount);

    drawing::drawDFA(*dfa, resultFileName);
    logger::log(Verbose(OPTIMIZER_V), File("result.txt"), ss.str());
}

void Optimizer::summarizeTool(DFA* tool){
    std::string dirpath = logger::settings::FULL_DIR_STR;
    std::string toolDirpath = dirpath + "/" + "tool";

    if (mkdir(toolDirpath.c_str(), 0777) < 0)
        if (errno !=EEXIST) ERR("mkdir");
    stringstream ssTool;

    ssTool << "Tool Summary" << std::endl;
    ssTool << *tool;

    std::string toolFileName = toolDirpath + "/" + "dfa_tool";
    //drawing::drawDFA(*tool, toolFileName);
    logger::log(Verbose(OPTIMIZER_V), File("result.txt"), ssTool.str());
}

void Optimizer::summarizeBestPSOResult(){
    const DFA* dfa = bestParticle->getBestDFA();

    // Build string for result
    stringstream ss;

    ss << "Best PSO Result" << std::endl;
    ss << *dfa << std::endl;
    ss << "Fitness:  " << bestParticle->getBestFitness() << std::endl;
    ss << "Test Set: " << bestTestingSetResult;

    logger::log(Verbose(OPTIMIZER_V), File("result.txt"), ss.str());
}
