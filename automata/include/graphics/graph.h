//
// Created by jakub on 12/1/15.
//

#ifndef AC_GRAPH_H
#define AC_GRAPH_H

#include <vector>
#include <string>

namespace gfx
{
    void drawGraph(int states, int symbols,
                   std::vector<int> transVec, std::string filename);
}

#endif //AC_GRAPH_H
