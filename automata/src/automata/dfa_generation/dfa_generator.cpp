//
// Created by jakub on 12/8/15.
//

#include <utils.h>
#include <fstream>
#include <sys/stat.h>
#include <error.h>
#include <loaders/dfa_loader.h>
#include <drawer.h>
#include "dfa_generator.h"

namespace automata
{

    void generateDFA(unsigned int stateCount, unsigned int symbolCount,
                     std::string dirpath){
        std::string DFA_EXT = ".dfa";

        std::string dfaStr = "";

        dfaStr += std::to_string(stateCount) + "," +
                    std::to_string(symbolCount) + ",";

        // Create Random Transition Function
        unsigned int transitionLength = stateCount * symbolCount;
        unsigned int min = 1;
        unsigned int max = stateCount;
        for(unsigned int i = 0; i < transitionLength; i++){

            unsigned int state = utils::generateRandomNumber(min, max+1);

            dfaStr += std::to_string(state);
            if(i != transitionLength-1){
                dfaStr += ",";
            }
        }

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
        DFA dfa = dfa_loader::loadDFA(filePathDFA);
        drawing::drawDFA(dfa, filePathDraw);
    }


}
