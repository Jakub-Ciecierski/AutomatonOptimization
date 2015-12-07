//
// Created by jakub on 12/7/15.
//

#include "node.h"

Node::Node(unsigned int index){
    this->index = index;

    color = "";
    label = "";
}

std::string Node::getColor(){
    return this->color;
}

std::string Node::getLabel(){
    return this->label;
}

unsigned int Node::getIndex(){
    return this->index;
}

void Node::setColor(std::string color){
    this->color = color;
}
void Node::setLabel(std::string label){
    this->label = label;
}

//-----------------------------------------------------------//
//  OPERATORS
//-----------------------------------------------------------//

bool Node::operator==(const Node& node) const{
    return this->index == node.index;
}