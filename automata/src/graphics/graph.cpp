//
// Created by jakub on 12/1/15.
//

#include <logger/logger_settings.h>
#include "graphviz/gvc.h"
#include "graph.h"

namespace gfx
{
    void drawGraph(int states, int symbols,
                   std::vector<int> transVec, std::string filename){
        Agraph_t *g;
        g = agopen("g", Agdirected, 0);

        std::vector<Agnode_t*> nodes(states);

        for(int i = 0; i < states; i++){
            std::string s = std::to_string(i);
            char const *pchar = s.c_str();

            nodes[i] = agnode(g, (char*)pchar, 1);
        }

        agsafeset(nodes[0], "color", "red", "");

        int size = transVec.size();
        int currentSymbol = 0;

        while(currentSymbol < symbols){
            std::string s = std::to_string(currentSymbol);
            char const *pchar = s.c_str();

            int start_i = states * currentSymbol;
            int fromNode = 0;

            for(int i = start_i; i < (start_i+states); i++){

                // -1 becouse the decoding starts indexing from 1
                int toNode = transVec[i] - 1;

                Agedge_t* e = agedge(g,
                                     nodes[fromNode],
                                     nodes[toNode],
                                     (char*)pchar, 1);

                agsafeset(e, "label", (char*)pchar, "");

                fromNode++;
            }
            currentSymbol++;
        }

        std::string filepath_dot = logger::settings::FULL_DIR_STR +
                                   "/" + filename + ".dot";
        std::string filepath_jpg = logger::settings::FULL_DIR_STR +
                                   "/" + filename + ".jpg";

        FILE *f = fopen( filepath_dot.c_str(), "w");

        agwrite(g, f);

        std::string command = "../graphviz/dot -Tjpg " + filepath_dot +
                              " -o " + filepath_jpg;

        system(command.c_str());

        fclose(f);

        agclose(g);

    }

}