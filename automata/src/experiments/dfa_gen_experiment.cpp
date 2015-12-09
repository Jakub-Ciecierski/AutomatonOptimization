//
// Created by jakub on 12/8/15.
//

#include <logger/log.h>
#include <settings/global_settings.h>
#include <dfa_generation/dfa_generator.h>
#include "dfa_gen_experiment.h"

namespace experiments
{

    void runDFAGenerationExperiment(){
        logger::log("DFA Generation Experiment Begin");

        std::stringstream ss;
        ss << "Generated DFA:" << std::endl;
        ss << "States#:   " << global_settings::GEN_DFA_STATES << std::endl;
        ss << "Symbols#:  " << global_settings::GEN_DFA_SYMBOLS << std::endl;
        ss << "File Path: " << global_settings::GEN_DFA_PATH;

        automata::generateRandomDFA(global_settings::GEN_DFA_STATES,
                                    global_settings::GEN_DFA_SYMBOLS,
                                    global_settings::GEN_DFA_PATH);

        logger::log(ss.str());

        logger::log("DFA Generation Experiment Finish");
    }

    namespace dfa_gen
    {
    }

}