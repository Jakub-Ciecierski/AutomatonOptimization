//
// Created by jakub on 12/8/15.
//

#include <utils.h>
#include <fstream>
#include <sys/stat.h>
#include <error.h>
#include <loaders/dfa_loader.h>
#include <drawer.h>
#include <algorithms/automata_algs.h>
#include <logger/log.h>
#include "dfa_generator.h"

namespace automata
{

    void generateRandomDFA(unsigned int stateCount, unsigned int symbolCount,
                           std::string dirpath){
        std::string DFA_EXT = ".dfa";
        std::string headerStr = "";
        std::string transitionStr = "";
        std::string dfaStr = "";
        int unreachableStateCount = 0;

        headerStr += std::to_string(stateCount) + "," +
                    std::to_string(symbolCount) + ",";

        do{
            transitionStr = "";
            dfaStr = "";

            // Create Random Transition Function
            unsigned int transitionLength = stateCount * symbolCount;
            unsigned int min = 1;
            unsigned int max = stateCount;
            for(unsigned int i = 0; i < transitionLength; i++){

                unsigned int state = utils::generateRandomNumber(min, max+1);

                transitionStr += std::to_string(state);
                if(i != transitionLength-1){
                    transitionStr += ",";
                }
            }
            dfaStr = headerStr + transitionStr;

            DFA* dfaRandom = dfa_loader::loadDFAFromString(dfaStr);
            unreachableStateCount =
                    automata::removeUnreachableStates(dfaRandom);
            delete dfaRandom;

            if(unreachableStateCount > 0)
                logger::log(Verbose(DEBUG_V), "Generated DFA with",
                            unreachableStateCount, " Unreachable States",
                            " Generating again");
        }while(unreachableStateCount != 0);

        if (mkdir(dirpath.c_str(), 0777) < 0)
            if (errno !=EEXIST) ERR("mkdir");

        // Save it unified format to file
        std::string fileName = "s" + std::to_string(stateCount) +
                                    "_r" + std::to_string( symbolCount);
        std::string fileNameDFA = fileName + DFA_EXT;
        std::string filePathDFA = dirpath + "/" + fileNameDFA;
        std::ofstream file;
        file.open(filePathDFA);
        if(!file.is_open()){
            throw std::invalid_argument("Could not open file: " + fileNameDFA);
        }
        file << dfaStr;
        file.close();

        // Draw created DFA
        std::string filePathDraw = dirpath + "/" + fileName;
        DFA* dfa = dfa_loader::loadDFAFromFile(filePathDFA);
        drawing::drawDFA(*dfa, filePathDraw);
    }


}
