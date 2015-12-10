//
// Created by jakub on 12/8/15.
//

#include <loaders/dfa_loader.h>
#include <drawer.h>
#include "optimizer_experiment.h"

namespace experiments
{

    void runOptimizerExperiment(){
        logger::log("Optimizer Experiment Begin");

        DFA* dfaTool = dfa_loader::loadDFAFromFile(global_settings::TOOL_URL);

        // Start Optimizer
        Optimizer opt(dfaTool);
        opt.start();

        logger::log("Optimizer Experiment Finish");

        delete dfaTool;
    }

}
