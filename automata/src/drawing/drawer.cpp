//
// Created by jakub on 12/7/15.
//

#include "drawer.h"
#include <logger/logger_settings.h>
#include <sstream>
#include <logger/log.h>

namespace drawing
{
    Graph* DFAToGraph(const DFA &dfa){
        Graph* g = new Graph();

        unsigned int stateCount = dfa.getStateCount();
        unsigned int symbolCount = dfa.getSymbolCount();

        unsigned int initialState = dfa.getInitialState();

        // Create nodes
        for(unsigned int i = 0; i < stateCount; i++){
            Node* node = new Node(i);
            node->setLabel(std::to_string(i));
            if(initialState == i){
                node->setColor("red");
            }

            g->addNode(node);
        }

        const std::vector<Node*>* nodes = g->getNodes();

        const TransitionFunction* tf = dfa.getTransitionFunction();

        unsigned int currentSymbol = 0;
        unsigned int currentState = 0;

        int edgeKey = 0;
        // Set up edges
        while(currentState < stateCount){
            currentSymbol = 0;
            while(currentSymbol < symbolCount){
                int toState;
                // toState - 1, We index states from 0
                toState = tf->getState(currentState, currentSymbol);

                std::string str = std::to_string(currentSymbol);

                if(toState != -1){
                    Edge* edge = new Edge((*nodes)[currentState],
                                          (*nodes)[toState],
                                          edgeKey++);
                    edge->setLabel(std::to_string(currentSymbol));
                    g->addEdge(edge);
                }
                currentSymbol++;
            }
            currentState++;
        }

        return g;
    }

    std::string graphToDOT(const Graph& graph){
        std::stringstream graphDOT;

        const std::vector<Node*>* nodes = graph.getNodes();
        const std::vector<Edge*>* edges = graph.getEdges();

        graphDOT << "digraph g {" << std::endl;

        // Create nodes
        for(unsigned int i = 0; i < nodes->size(); i++){
            Node* node = (*nodes)[i];
            std::string label = node->getLabel();
            std::string color = node->getColor();

            graphDOT << node->getKey();
            if(!label.empty()){
                graphDOT << " [label= \"" << label << "\"]";
            }
            if(!color.empty()){
                graphDOT << " [color=\"" << color << "\"]";
            }

            graphDOT << ";" << std::endl;
        }

        // Create edges
        for(unsigned int i = 0; i < edges->size(); i++){
            Edge* edge = (*edges)[i];
            Node* node1 = edge->getNode1();
            Node* node2 = edge->getNode2();

            std::string label = edge->getLabel();
            std::string color = edge->getColor();

            graphDOT << node1->getKey() << " -> " << node2->getKey();

            if(!label.empty()){
                graphDOT << "[label= \"" << label << "\"]";
            }
            if(!color.empty()){
                graphDOT << "[color=\"" << color << "\"]";
            }

            graphDOT << ";" << std::endl;
        }

        graphDOT << "}" << std::endl;

        return graphDOT.str();
    }

    //--------------------------------------------------------------------------

    void drawDFA(const DFA& dfa, std::string filepath){
        Graph* g = DFAToGraph(dfa);

        g->combineParallelEdges();

        drawGraph(*g, filepath);

        delete g;
    }


    void drawGraph(const Graph &graph, std::string filepath){
        std::string graphDOT = graphToDOT(graph);

        std::string filepath_dot = filepath + ".dot";
        std::string filepath_jpg = filepath + ".jpg";

        std::ofstream fileStream;
        fileStream.open(filepath_dot.c_str());
        fileStream << graphDOT;
        fileStream.close();
        
        logger::log(Verbose(DEBUG_V),
                    "Drawing Graph. Input File\n", filepath_jpg);


        std::string command5 = "./res/dot5/dot -Tjpg " + filepath_dot +
                              " -o " + filepath_jpg;

        std::string command6 = "./res/dot6/dot -Tjpg " + filepath_dot +
                              " -o " + filepath_jpg;

        int ret = system(command6.c_str());
        if(ret != 0){
            system(command5.c_str());
        }
    }
}
