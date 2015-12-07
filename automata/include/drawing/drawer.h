//
// Created by jakub on 12/7/15.
//

#ifndef AC_DRAWGRAPH1_H
#define AC_DRAWGRAPH1_H

#include "graph.h"
#include <dfa.h>

namespace drawing
{
    /*
     * Transform DFA to Graph
     */
    Graph* DFAToGraph(const DFA &dfa);

    /*
     * Returns a string  contatining DOT language describing input Graph
     */
    std::string graphToDOT(const Graph& graph);


    /*
     * Draws DFA and saves it in filepath.
     * DFA is transformed into Graph and then drawn as such
     */
    void drawDFA(const DFA& dfa, std::string filepath);

    /*
     * Draws a Graph and saves it in filepath
     */
    void drawGraph(const Graph &graph, std::string filepath);
}

#endif //AC_DRAWGRAPH1_H
