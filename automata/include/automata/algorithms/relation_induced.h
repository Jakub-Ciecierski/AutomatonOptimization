//
// Created by jakub on 12/5/15.
//

#ifndef AC_RELATION_INDUCED_H
#define AC_RELATION_INDUCED_H

#include <word.h>
#include "dfa.h"

namespace automata
{
    bool isInRelationInduced(const DFA &dfa, const Word &w1, const Word &w2);
}

#endif //AC_RELATION_INDUCED_H
