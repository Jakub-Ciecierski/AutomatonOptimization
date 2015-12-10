//
// Created by jakub on 12/8/15.
//

#ifndef AC_DFA_GENERATOR_H
#define AC_DFA_GENERATOR_H

#include <string>

namespace automata
{

    /*
     * Generates Random DFA and saves it in directory given by dirpath.
     * If dirpath does not exist, it will be created
     * Generated DFA has no unreachable states
     *
     * Saves the DOT, JPG, DFA format files
     * DOT - The graph representing DFA in DOT language.
     * JPG - The graph visualization in jpg format
     * DFA - the Unified Form of representing DFA.
     */
    void generateRandomDFA(unsigned int stateCount, unsigned int symbolCount,
                           std::string dirpath);
}
#endif //AC_DFA_GENERATOR_H
