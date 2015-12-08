//
// Created by jakub on 12/8/15.
//

#ifndef AC_DFA_GENERATOR_H
#define AC_DFA_GENERATOR_H

#include <string>

namespace automata
{

    void generateDFA(unsigned int stateCount, unsigned int symbolCount,
                        std::string dirpath);
}
#endif //AC_DFA_GENERATOR_H
