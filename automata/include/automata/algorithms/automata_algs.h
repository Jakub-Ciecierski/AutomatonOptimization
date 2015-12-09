//
// Created by jakub on 12/9/15.
//

#ifndef AC_AUTOMATA_ALGS_H
#define AC_AUTOMATA_ALGS_H

#include <dfa.h>
#include <map>

namespace automata
{
    const unsigned int STATE_ON = 1;
    const unsigned int STATE_OFF = 0;

    /*
     * Finds and removes Unreachable states.
     * Uses getReachabilityFlags and reduceDFA
     *
     * Returns the number of removed states;
     *
     */
    unsigned int removeUnreachableStates(DFA* dfa);

    /*
     * Returns a flag of states Reachability.
     * States that are reachable get flag value:    STATE_ON
     * States that are unreachable get flag value:  STATE_OFF
     *
     * Allocates memory for Flag vector. It takes no responsibility of
     * deleting this memory.
     *
     * Finds.
     * 1) All states reachable from initial state are Reachable
     * 2) All states reachable from Reachable states are Reachable
     * 3) Repeat 2) until no further changes are made
     */
    std::vector<unsigned int>* getReachabilityFlags(DFA* dfa);

    /*
     * Reduce the DFA with regards to reduction flags.
     * States flags as STATE_OFF will be removed.
     *
     * Returns a map of states of original and reduced DFA
     * map[1] = 0
     *  Means that state 1 in original DFA is now state 0 in reduced DFA.
     * map[2] = -1
     *  Means that state 2 has been removed and has no mapping
     *
     * Allocated memory for the map. It should be removed manually.
     */
    std::map<int, int>* reduceDFA(DFA* dfa,
                           std::vector<unsigned int>* reductionFlags);
}

#endif //AC_AUTOMATA_ALGS_H
