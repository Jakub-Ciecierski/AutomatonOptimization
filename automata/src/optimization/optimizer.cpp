//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"

#include <set>
#include <drawer.h>
#include <sys/stat.h>
#include <error.h>

#include "relation_induced.h"
#include "automata_algs.h"

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

    _wordsGenerator = new WordsGenerator(global_settings::WORDS_PATH);
}

void Optimizer::computeRelation() {
    logger::log(Verbose(OPTIMIZER_V), "Computing Relation");

    const vector<Word*>* trainingSet = _wordsGenerator->getTrainingAllSet();
    unsigned int wordCount = trainingSet->size();

    vector<int> stateVector(wordCount);

    // Pre compute all words. Save results in stateVector
    for(unsigned int i = 0; i < wordCount; i++){
        Word* word = (*trainingSet)[i];
        stateVector[i] = tool->compute(*word);
    }

    // For all distinct pairs
    for(unsigned int i = 0; i < wordCount-1; i++){
        for(unsigned int j = i+1; j < wordCount; j++){
            bool inRelation = stateVector[i] == stateVector[j];
            int result = inRelation ? 1:0;
            _toolRelationResults.push_back(result);
        }
    }
}

double Optimizer::computeError(Particle* particle,
                                        const std::vector<Word*>* set) {
    const DFA* dfaResult = particle->getBestDFA();

    int count = 0;
    int pairCount = 0;

    unsigned int wordCount = set->size();

    vector<int> stateVectorResult(wordCount);
    vector<int> stateVectorTool(wordCount);

    // Pre compute all words. Save results in stateVector
    for(unsigned int i = 0; i < wordCount; i++){
        Word* word = (*set)[i];
        stateVectorResult[i] = dfaResult->compute(*word);
        stateVectorTool[i] = tool->compute(*word);
    }

    std::vector<int> toolRelation;
    // For all distinct pairs
    for(unsigned int i = 0; i < wordCount-1; i++){
        for(unsigned int j = i+1; j < wordCount; j++){
            bool inRelationResult = 
                    (stateVectorResult[i] == stateVectorResult[j]);
            bool inRelationTool = 
                    (stateVectorTool[i] == stateVectorTool[j]);
            count += (inRelationResult == inRelationTool) ? 1:0;
            
            pairCount++;
        }
    }

    double result = count / (double) pairCount;

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

    double testSetResult =
            computeError(bestPSOResult, _wordsGenerator->getTestSet());

    double trainingShortResult =
            computeError(bestPSOResult, _wordsGenerator->getTrainingShortSet());

    double trainingLongResult =
            computeError(bestPSOResult, _wordsGenerator->getTrainingLongSet());

    double trainingAllResult =
            computeError(bestPSOResult, _wordsGenerator->getTrainingAllSet());

    compareResultWithBestResult(bestPSOResult, testSetResult);

    std::string info = "PSO Result Summary - States = " + std::to_string(s);
    summarize(bestPSOResult, s,
              testSetResult,
              trainingShortResult,
              trainingLongResult,
              trainingAllResult,info);

    delete pso;
}

Particle *Optimizer::selectParticleUsingMinimumStates(
        const std::vector<Particle *>& results) {
    const vector<Word*>* wordSet = _wordsGenerator->getTrainingAllSet();
    std::vector<std::set<int>> stateCountVec;

    // For each result check how many states it uses.
    for (unsigned int i = 0; i < results.size(); i++) {
        Particle* result = results[i];
        const DFA* dfa = result->getBestDFA();

        std::set<int> s;

        unsigned int wordCount = wordSet->size();
        vector<int> stateVector(wordCount);
        // Pre compute all words. Save results in stateVector
        for(unsigned int i = 0; i < wordCount; i++){
            Word* word = (*wordSet)[i];
            stateVector[i] = dfa ->compute(*word);
            s.insert(dfa->compute(*word));
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
        bestTestingSetResult = testSetResult;
    }
    else if (bestTestingSetResult < testSetResult){
        delete this->bestParticle;
        this->bestParticle = new Particle(*particle);

        bestTestingSetResult = testSetResult;
    }
}

void Optimizer::summarize(Particle* particle, int psoStateCount,
                            double testSetResult,
                            double trainingShortResult,
                            double trainingLongResult,
                            double trainingAllResult,
                            std::string headerInfo){
    std::string dirpath = logger::settings::FULL_DIR_STR;

    const DFA* dfa = particle->getBestDFA();
    DFA* reducedDFA = new DFA(*dfa);
    double unreachableCount = automata::removeUnreachableStates(&reducedDFA);

    // Build string for result
    stringstream ss;

    ss << headerInfo << std::endl;
    ss << *dfa << std::endl;
    ss << "Fitness:             " << particle->getBestFitness() << std::endl;
    ss << "Test Set:            " << testSetResult  << std::endl;
    ss << "Train Short Set:     " << trainingShortResult  << std::endl;
    ss << "Train Long Set:      " << trainingLongResult  << std::endl;
    ss << "Train All            " << trainingAllResult << std::endl;
    ss << "Unreachable Count    " << unreachableCount;

    std::string resultDirpath = dirpath + "/" +
            "pso_s" + std::to_string(psoStateCount);

    if (mkdir(resultDirpath.c_str(), 0777) < 0)
        if (errno !=EEXIST) ERR("mkdir");

    std::string resultFileName =
            resultDirpath + "/" +
                    "dfa_result_pso_s" +  std::to_string(psoStateCount);

    drawing::drawDFA(*reducedDFA, resultFileName);
    logger::log(Verbose(OPTIMIZER_V), File("result.txt"), ss.str());

    delete reducedDFA;
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
