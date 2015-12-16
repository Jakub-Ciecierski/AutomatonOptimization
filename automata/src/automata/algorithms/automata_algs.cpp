//
// Created by jakub on 12/9/15.
//

#include <logger/log.h>
#include <deque>
#include "automata_algs.h"

namespace automata
{

    unsigned int removeUnreachableStates(DFA** dfa){
        std::vector<unsigned int>* reachibilityFlags =
                                getReachabilityFlags(*dfa);

        unsigned int reducedCount = 0;
        for(unsigned int i = 0; i < reachibilityFlags->size(); i++){
            if((*reachibilityFlags)[i] == STATE_OFF)
                reducedCount++;
        }

        std::map<int, int>* mapping = reduceDFA(dfa, reachibilityFlags);

        delete mapping;
        delete reachibilityFlags;

        return reducedCount;
    }

    std::vector<unsigned int>* getReachabilityFlags(DFA* dfa){
        const TransitionFunction* tf = dfa->getTransitionFunction();

        unsigned int stateCount = dfa->getStateCount();
        unsigned int symbolCount = dfa->getSymbolCount();
        unsigned int initialState = dfa->getInitialState();

        // Reachable Flags - 0 unreachable, 1 reachable.
        std::vector<unsigned int>* reachableFlags =
                new std::vector<unsigned int>(stateCount);
        for(unsigned int i = 0; i < stateCount; i++){
            (*reachableFlags)[i] = STATE_OFF;
        }
        (*reachableFlags)[initialState] = STATE_ON;

        // Current Nodes to start reachability test from.
        // These Nodes are necessarily reachable
        std::deque<unsigned int> currentNodes;
        // Start from initial state
        currentNodes.push_back(initialState);

        bool do_continue = true;
        while(do_continue){
            do_continue = false;
            while(!currentNodes.empty()){
                unsigned int currState = currentNodes.back();
                currentNodes.pop_back();

                for(unsigned int r = 0; r < symbolCount; r++){
                    int toState = tf->getState(currState, r);
                    // If it is not undefined
                    if(toState != -1){
                        // If it is not already in
                        if((*reachableFlags)[toState] != STATE_ON){
                            (*reachableFlags)[toState] = STATE_ON;
                            currentNodes.push_back(toState);
                            do_continue = true;
                        }
                    }
                }
            }
        }
        return reachableFlags;
    }

    std::map<int, int>* reduceDFA(DFA** dfa,
                                  std::vector<unsigned int>*reductionFlags){
        const TransitionFunction* tf = (*dfa)->getTransitionFunction();
        unsigned int stateCount = (*dfa)->getStateCount();
        unsigned int symbolCount = (*dfa)->getSymbolCount();

        unsigned int unreachableCount = 0;
        unsigned int currentReducedState = 0;

        std::map<int, int>* statesMapping = new std::map<int, int>;
        for(unsigned int i = 0; i < stateCount; i++){
            if((*reductionFlags)[i] == STATE_ON){
                (*statesMapping)[i] = currentReducedState;
                currentReducedState++;
            }else{
                (*statesMapping)[i] = -1;
                unreachableCount++;
            }
        }

        unsigned int reducedStateCount = stateCount - unreachableCount;

        if(unreachableCount > 0) {
            TransitionFunction *tfReduced =
                    new TransitionFunction(reducedStateCount, symbolCount);

            for (unsigned int s = 0; s < stateCount; s++) {
                if((*statesMapping)[s] != -1)
                    for (unsigned int r = 0; r < symbolCount; r++) {
                        int toState = tf->getState(s, r);

                        if((*statesMapping)[toState] != -1)
                            tfReduced->addTransition((*statesMapping)[s],
                                                     r,
                                                     (*statesMapping)[toState]);
                    }
            }

            delete *dfa;
            *dfa = new DFA(tfReduced);
        }

        return statesMapping;
    }
}