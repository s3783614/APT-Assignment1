#include "PathSolver.h"
#include <iostream>
#include <unistd.h>

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env){

    Node* startNode = new Node(0,0,0);
    Node* goalNode = new Node(0,0,0);
    Node* currentNode = new Node(0,0,0);
    
    Node* tempNode = new Node(0,0,10000);
    Node* closest = nullptr;

    NodeList* openList = new NodeList();
    closedList = new NodeList();

    for(int row = 0; row < ENV_DIM; row++){
        for(int col = 0; col < ENV_DIM; col++){

            if(env[row][col] == SYMBOL_GOAL){
                delete goalNode;
                
                goalNode = new Node(row,col,0);
            }
            else if(env[row][col] == SYMBOL_START){
                delete startNode;
                startNode = new Node(row,col,0);
                openList->addElement(startNode);
            }
        }
    }

    delete currentNode;
    currentNode = startNode;

    do{

        //checks the top character to see for free space - then checks for the node in availability
        if((currentNode->readTopCharacter(env) == SYMBOL_EMPTY || currentNode->readTopCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getTopNode(env)) && !closedList->contains(currentNode->getTopNode(env)) )
            {
                Node* tempTopNode = new Node(currentNode->getRow()-1, currentNode->getCol(), currentNode->getDistanceTraveled()+1); 
                openList->addElement(tempTopNode);
                delete tempTopNode;
            }
        
        if((currentNode->readBottomCharacter(env) == SYMBOL_EMPTY || currentNode->readBottomCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getBottomNode(env)) && !closedList->contains(currentNode->getBottomNode(env)) )
            {
                Node* tempBottomNode = new Node(currentNode->getRow()+1, currentNode->getCol(), currentNode->getDistanceTraveled()+1);
                openList->addElement(tempBottomNode);
                delete tempBottomNode;
            }
        
        if((currentNode->readLeftCharacter(env) == SYMBOL_EMPTY || currentNode->readLeftCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getLeftNode(env)) && !closedList->contains(currentNode->getLeftNode(env)) )
            {
                Node* tempLeftNode = new Node(currentNode->getRow(), currentNode->getCol()-1, currentNode->getDistanceTraveled()+1);
                openList->addElement(tempLeftNode);
                delete tempLeftNode;
            }
        
        if((currentNode->readRightCharacter(env) == SYMBOL_EMPTY || currentNode->readRightCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getRightNode(env)) && !closedList->contains(currentNode->getRightNode(env)) )
            {
                Node* tempRightNode = new Node(currentNode->getRow(), currentNode->getCol()+1, currentNode->getDistanceTraveled()+1); 
                openList->addElement(tempRightNode);
                delete tempRightNode;
            }

        closest = tempNode;

        for(int i = 0; i < openList->getLength(); i++){

            if(openList->getNode(i)->getEstimatedDist2Goal(goalNode) < closest->getEstimatedDist2Goal(goalNode) &&
              !closedList->contains(*(openList->getNode(i))) && !openList->getNode(i)->equalTo(*currentNode) ){

                closest = openList->getNode(i);

            }

        }
        
        closedList->addElement(currentNode);

        currentNode = closest;

    }
    while(!closedList->getNode(closedList->getLength() - 1)->equalTo(*goalNode) 
          && openList->getLength() != closedList->getLength());

    nodesExplored = new NodeList(*closedList);

    delete goalNode;
    delete startNode;

    delete tempNode;

    delete openList;
    delete closedList;

}

NodeList* PathSolver::getNodesExplored(){
    return new NodeList(*nodesExplored);
}


NodeList* PathSolver::getPath(Env env){
    // TODO

    NodeList* finalPath = new NodeList();

    Node* goal = nodesExplored->getNode(nodesExplored->getLength()-1);

    for(int i = nodesExplored->getLength()-1; i > 0; i--){

        if(nodesExplored->getNode(i)->getDistanceTraveled() ==
          (goal->getDistanceTraveled()-1) )
        {

            if(goal->getTopNode(env).equalTo(*(nodesExplored->getNode(i))) ||
               goal->getBottomNode(env).equalTo(*(nodesExplored->getNode(i))) ||
               goal->getLeftNode(env).equalTo(*(nodesExplored->getNode(i))) ||
               goal->getRightNode(env).equalTo(*(nodesExplored->getNode(i))) )
            {

                goal = nodesExplored->getNode(i);

                finalPath->addElement(goal);

            }

        }

    }

    return finalPath;
}

//-----------------------------

void PathSolver::printSolution(Env env, NodeList* closedList){

    for(int row = 0; row < ENV_DIM; row++){
        for(int col = 0; col < ENV_DIM; col++){

            if(closedList->contains(Node(row,col,0))){
                std::cout << "x";
            }
            else{
                std::cout << env[row][col];
            }
            
        }
        std::cout << " " << row << std::endl;
    }

}

void PathSolver::printMovement(Env env, Node currentNode){
    for(int row = 0; row < ENV_DIM; row++){
        for(int col = 0; col < ENV_DIM; col++){
            if(row == currentNode.getRow() && col == currentNode.getCol()){
                std::cout << "*";
            }
            else{
                std::cout << env[row][col];
            }
        }
        std::cout << std::endl;

    }
}