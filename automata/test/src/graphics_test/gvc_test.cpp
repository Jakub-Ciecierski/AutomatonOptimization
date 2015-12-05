//
// Created by jakub on 12/1/15.
//

#include <gtest/gtest.h>

#include "graphviz/gvc.h"


//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void drawGraph();

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void drawGraph(){
    char* charGraphName = (char*)"g";
    char* labelColorStr = (char*)"color";
    char* colorStr = (char*)"red";
    char* emptyStr = (char*)"";
    char* labelLabelStr = (char*)"label";

    int states = 3;
    int symbols = 2;
    std::vector<int> transVec{3,2,3,
                              2,2,3};

    Agraph_t *g;
    g = agopen(charGraphName, Agdirected, 0);

    std::vector<Agnode_t*> nodes(states);

    std::cout << "Creating Nodes" << std::endl;

    for(int i = 0; i < states; i++){
        std::string s = std::to_string(i);
        char const *pchar = s.c_str();

        nodes[i] = agnode(g, (char*)pchar, 1);
    }


    agsafeset(nodes[0], labelColorStr , colorStr , emptyStr);
    
    int currentSymbol = 0;

    while(currentSymbol < symbols){
        std::string s = std::to_string(currentSymbol);
        char const *pchar = s.c_str();

        int start_i = states * currentSymbol;
        int fromNode = 0;

        for(int i = start_i; i < (start_i+states); i++){

            // -1 becouse the decoding starts indexing from 1
            int toNode = transVec[i] - 1;

            std::cout << "toNode: " << toNode << std::endl;
            std::cout << "fromNode: " << fromNode << std::endl;

            Agedge_t* e = agedge(g,
                                 nodes[fromNode],
                                 nodes[toNode],
                                 (char*)pchar, 1);

            agsafeset(e, labelLabelStr, (char*)pchar, emptyStr);

            fromNode++;
        }
        currentSymbol++;
    }

    agwrite(g, stdout);

    agclose(g);
}


//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//


TEST(GVC, Install){
    //drawGraph();
}