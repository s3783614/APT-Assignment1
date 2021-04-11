#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    // TODO
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    // TODO
    // delete row;
    // delete col;
    // delete dist_traveled;
}

int Node::getRow(){
    // TODO
    return row;
}

int Node::getCol(){
    // TODO
    return col;
}

int Node::getDistanceTraveled(){
    // TODO
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    // TODO
    this->dist_traveled = dist_traveled;
    // this->dist_traveled = dist_traveled + 1;

}

int Node::getEstimatedDist2Goal(Node* goal){
    // TODO
    manhatten_distance = std::abs(this->col - goal->getCol()) + std::abs(this->row - goal->getRow());
     
    return (this->dist_traveled) + (manhatten_distance);


}
    
//--------------------------------

bool Node::equalTo(Node node){
    bool checker = false;

    if(this->row == node.getRow() && this->col == node.getCol()){
        checker = true;
    }
    return checker;
}

char Node::readTopCharacter(Env env){
    int rowRead = (this->row-1);
    int colRead = (this->col);
    return env[rowRead][colRead];
}

char Node::readBottomCharacter(Env env){
    int rowRead = (this->row + 1);
    int colRead = (this->col);
    return env[rowRead][colRead];
}

char Node::readLeftCharacter(Env env){
    int rowRead = (this->row);
    int colRead = (this->col - 1);
    return env[rowRead][colRead];
}

char Node::readRightCharacter(Env env){
    int rowRead = (this->row);
    int colRead = (this->col + 1);
    return env[rowRead][colRead];
}


Node Node::getTopNode(Env env){
    int rowRead = (this->row-1);
    int colRead = (this->col);
    int distTravRead = (this->dist_traveled+1);
    return Node(rowRead, colRead, distTravRead);
}

Node Node::getBottomNode(Env env){
    int rowRead = (this->row+1);
    int colRead = (this->col);
    int distTravRead = (this->dist_traveled+1);
    return Node(rowRead, colRead, distTravRead);
}

Node Node::getLeftNode(Env env){
    int rowRead = (this->row);
    int colRead = (this->col-1);
    int distTravRead = (this->dist_traveled+1);
    return Node(rowRead, colRead, distTravRead);
}

Node Node::getRightNode(Env env){
    int rowRead = (this->row);
    int colRead = (this->col+1);
    int distTravRead = (this->dist_traveled+1);
    return Node(rowRead, colRead, distTravRead);
}


