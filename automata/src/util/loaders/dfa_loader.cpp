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
    DFA* loadDFAFromFile(std::string dfaURL) {
        ifstream file;
        file.open(dfaURL);

        stringstream ss;
        if(!file.is_open()){
            throw std::invalid_argument("File not found" + dfaURL);
        }

        std::string str;
        std::getline(file, str);

        file.close();

        DFA* dfa = loadDFAFromString(str);

        logger::log(Verbose(DEBUG_V),"Loaded DFA from file:\n", dfaURL);

        return dfa;
    }

    DFA* loadDFAFromString(std::string dfaUnifiedForm){
        std::vector<std::string> entries_str =
                str_util::splitString(dfaUnifiedForm,",");

        unsigned int stateCount = stoi(entries_str[0]);
        unsigned int symbolCount = stoi(entries_str[1]);

        unsigned int len = stateCount*symbolCount;

        if(entries_str.size() != (len + 2)){
            std::cout << entries_str.size() << std::endl;
            std::cout << "Length: " << len << std::endl;
            throw std::invalid_argument("Wrong content in : " + dfaUnifiedForm);
        }

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

        DFA* dfa = new DFA(tf);

        return dfa;
    }
}