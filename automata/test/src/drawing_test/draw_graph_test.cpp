//
// Created by jakub on 12/7/15.
//
//
// Created by jakub on 11/14/15.
//


#include <gtest/gtest.h>
#include "drawer.h"

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void draw_test();

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void draw_test(){
    Graph graph;

    Node* node0 = new Node(0);
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);

    node0->setLabel("0");
    node0->setColor("red");

    node1->setLabel("1");
    node2->setLabel("2");
    node3->setLabel("3");

    Edge* edge0 = new Edge(node0, node0, 0);
    edge0->setLabel("0");
    Edge* edge1 = new Edge(node0, node0, 1);
    edge1->setLabel("1");

    Edge* edge2 = new Edge(node0, node1, 2);
    edge2->setLabel("1");

    Edge* edge3 = new Edge(node0, node2, 3);
    edge3->setLabel("2");

    Edge* edge4 = new Edge(node2, node2, 4);
    edge4->setLabel("0");
    Edge* edge5 = new Edge(node2, node2, 5);
    edge5->setLabel("1");

    graph.addNode(node0);
    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);

    graph.addEdge(edge0);
    graph.addEdge(edge1);
    graph.addEdge(edge2);
    graph.addEdge(edge3);
    graph.addEdge(edge4);
    graph.addEdge(edge5);

    graph.combineParallelEdges();

    drawing::drawGraph(graph, "test");
}

/*
 * Tests shows how to use random discrete distribution from
 * a vector of distributions.
 */
TEST(Graph, DrawGraph) {
    //draw_test();
}


