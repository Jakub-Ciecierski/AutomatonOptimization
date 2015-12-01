//
// Created by jakub on 12/1/15.
//

#ifndef AC_GRAPH_H
#define AC_GRAPH_H

#include <vector>
#include <string>

/*
 * Draws graphs of automaton to file.
 * TODO Need to run application in ./automata directory
 */
namespace gfx
{
    /*
     * Draws a graph and saves it in file.
     * Transition vector must be in Natural Decoding
     */
    void drawGraph(int states, int symbols,
                   std::vector<int> transVec, std::string filename);
}

#endif //AC_GRAPH_H
