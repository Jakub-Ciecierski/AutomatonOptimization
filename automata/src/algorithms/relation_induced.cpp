//
// Created by jakub on 12/5/15.
//

#include "relation_induced.h"

namespace automata
{
    bool isInRelationInduced(const DFA &dfa, const Word &w1, const Word &w2){
        int state1 = dfa.compute(w1);
        int state2 = dfa.compute(w2);

        return (state1 == state2);
    }
}