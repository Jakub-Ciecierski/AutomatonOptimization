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

        DFA dfaTool = dfa_loader::loadDFA(global_settings::TOOL_URL);

        logger::log("Starting Optimizer");
        // Start Optimizer
        Optimizer opt(&dfaTool);
        opt.start();
        logger::log("Optimizer Finished");

        // Print summary
        optimizer::summarize(opt);

        logger::log("Optimizer Experiment Finish");
    }

    namespace optimizer
    {
        void summarize(Optimizer &opt){
            const Particle* result = opt.getBestParticle();

            const DFA * dfa = result->getBestDFA();

            // Build string for result
            stringstream ss;
            ss << "Result Summary" << std::endl;

            ss << *dfa;
            ss << "Fitness: " << result->getBestFitness();

            drawing::drawDFA(*dfa, "dfa_result");

            stringstream ssTool;
            const DFA * tool = opt.getTool();

            ssTool << "Tool Summary" << std::endl;
            ssTool << *tool;

            drawing::drawDFA(*tool, "dfa_tool");

            logger::log(File("result.txt"), ss.str());
            logger::log(File("result.txt"), ssTool.str());
        }
    }

}
