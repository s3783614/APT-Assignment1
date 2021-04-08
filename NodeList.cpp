#include "NodeList.h"
#include <iostream>

//constructor
NodeList::NodeList(){
    // TODO
    this->length = 0;
}

//destructor
NodeList::~NodeList(){
    // TODO
    
    for(int i = 0; i < this->length; i++){
        // std::cout << "deconstructor called" << std::endl;
        delete this->getNode(i);
    }
    
}

//deep copy constructor
NodeList::NodeList(NodeList& other){
    // TODO
    this->length = other.length;
    
    for(int i = 0; i < other.length;i++){
        nodes[i] = new Node(other.getNode(i)->getRow(), 
        other.getNode(i)->getCol(),
        other.getNode(i)->getDistanceTraveled());
    }
}

int NodeList::getLength(){
    // TODO
    return length;
}

void NodeList::addElement(Node* newPos){
    // TODO
    nodes[length] = new Node(newPos->getRow(), newPos->getCol(), newPos->getDistanceTraveled());
    length++;
}

Node* NodeList::getNode(int i){
    // TODO
    return nodes[i];
}

//-----------------------------

bool NodeList::contains(Node node){
    bool found = false;
    for(int i = 0; i < this->length; i++){

        if(this->getNode(i)->equalTo(node)){
            found = true;
        }
    }
    return found;
}

