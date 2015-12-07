//
// Created by jakub on 12/4/15.
//

#include "dfa_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_utils.h>
#include <logger/log.h>
#include <settings/global_settings.h>

namespace dfa_loader
{
    DFA loadDFA(std::string dfaURL) {
        ifstream file;
        file.open(dfaURL);

        stringstream ss;
        if(!file.is_open()){
            throw std::invalid_argument("File not found" + dfaURL);
        }

        std::string str;
        std::getline(file, str);

        std::vector<std::string> entries_str = str_util::splitString(str,",");

        unsigned int stateCount = stoi(entries_str[0]);
        unsigned int symbolCount = stoi(entries_str[1]);

        TransitionFunction* tf = new TransitionFunction(stateCount,
                                                        symbolCount);

        unsigned int currentState = 0;
        unsigned int currentSymbol = 0;
        unsigned int counter = 0;

        while(currentState < stateCount){
            currentSymbol = 0;
            while(currentSymbol < symbolCount){
                // We start from counter + 2 since we read 2 first entries
                unsigned int toState = stoi(entries_str[(counter++) + 2]);

                // toState - 1, We index states from 0
                tf->addTransition(currentState, currentSymbol, toState-1);

                currentSymbol++;
            }
            currentState++;
        }

        file.close();

        DFA dfa(tf);

        logger::log(Verbose(DEBUG_V),"Loaded DFA from file:\n", dfaURL);

        return dfa;
    }
}