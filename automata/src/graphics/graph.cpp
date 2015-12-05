//
// Created by jakub on 12/1/15.
//

#include <logger/logger_settings.h>
#include <logger/log.h>
#include "graphviz/gvc.h"
#include "graph.h"

namespace graphics
{
    void drawGraph(const DFA & dfa, std::string filename){
        char* charGraphName = (char*)"g";
        char* labelColorStr = (char*)"color";
        char* colorStr = (char*)"red";
        char* emptyStr = (char*)"";
        char* labelLabelStr = (char*)"label";

        unsigned int stateCount = dfa.getStateCount();
        unsigned int symbolCount = dfa.getSymbolCount();

        Agraph_t *g;

        g = agopen(charGraphName, Agdirected, 0);

        std::vector<Agnode_t*> nodes(stateCount);

        // Create nodes corresponding to states
        for(unsigned int i = 0; i < stateCount; i++){
            std::string s = std::to_string(i);
            char const *pchar = s.c_str();

            nodes[i] = agnode(g, (char*)pchar, 1);
        }

        // First state colored in red

        agsafeset(nodes[0], labelColorStr , colorStr , emptyStr);

        unsigned int currentState = 0;
        unsigned int currentSymbol = 0;

        const TransitionFunction* tf = dfa.getTransitionFunction();

        // Set up edges
        while(currentState < stateCount){
            currentSymbol = 0;
            while(currentSymbol < symbolCount){
                int toState;
                // toState - 1, We index states from 0
                toState = tf->getState(currentState, currentSymbol);

                std::string str = std::to_string(currentSymbol);
                char const *pchar = str.c_str();

                if(toState != -1){
                    Agedge_t* e = agedge(g, nodes[currentState],
                                            nodes[toState],
                                            (char*)pchar, 1);

                    agsafeset(e, labelLabelStr, (char*)pchar, emptyStr);
                }
                currentSymbol++;
            }
            currentState++;
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