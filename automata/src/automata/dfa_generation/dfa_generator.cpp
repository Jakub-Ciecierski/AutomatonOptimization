//
// Created by jakub on 12/8/15.
//

#include <utils.h>
#include <fstream>
#include "dfa_generator.h"

namespace automata
{

    void generateDFA(unsigned int stateCount, unsigned int symbolCount,
                     std::string filepath){
        std::string dfaStr = "";

        dfaStr += std::to_string(stateCount) +
                "," +
                std::to_string(symbolCount) +
                ",";

        unsigned int transitionLength = stateCount * symbolCount;
        unsigned int min = 1;
        unsigned int max = stateCount;
        for(unsigned int i = 0; i < transitionLength; i++){

            unsigned int state = utils::generateRandomNumber(min, max);

            dfaStr += std::to_string(state);
            if(i != transitionLength-1){
                dfaStr += ",";
            }
        }
        std::ofstream file;
        file.open(filepath);
        if(!file.is_open()){
            throw std::invalid_argument("Could not open file: " + filepath);
        }

        file << dfaStr;

        file.close();
    }


}