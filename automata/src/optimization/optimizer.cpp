//
// Created by jakub on 11/15/15.
//

#include "optimizer.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Optimizer::Optimizer(string toolUrl) : tool(toolUrl) {
    _wordsGenerator = NULL;
}

Optimizer::~Optimizer(){
    delete _wordsGenerator;
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
        runPSO(s, r);
    }

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

void Optimizer::runPSO(int s, int r) {
    std::cout << "Running PSO. States #: " << s
        << " Symbols #: " << r << std::endl;

    pso = new PSO(s, r, &_toolRelationResults, _wordsGenerator);

    pso->compute();

    std::vector<Particle*> results = pso->results();

    for(unsigned int i = 0;i < results.size(); i++) {
        cout << "Result(" << i << "): Fitness = "
        << results[i]->bestFitness << "\n"
        << "pbest = " << results[i]->pbest << std::endl;
    }

    delete pso;
}