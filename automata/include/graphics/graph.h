//
// Created by jakub on 12/1/15.
//

#ifndef AC_GRAPH_H
#define AC_GRAPH_H

#include <vector>
#include <string>
#include "dfa.h"

/*
 * Draws graphs of automaton to file.
 * TODO Need to run application in ./automata directory
 */
namespace graphics
{
    /*
     * Draws a dfa in a form of a graph and saves it in file.
     */
    void drawGraph(const DFA & dfa, std::string filename);
}

#endif //AC_GRAPH_H
