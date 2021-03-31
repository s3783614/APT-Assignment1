#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
    this->nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    // TODO
    delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env){
    // not need
    
    Node* startNode = new Node(0,0,0);//ini to nullptr
    Node* goalNode = new Node(0,0,0);
    Node* currentNode = new Node(0,0,0);


    NodeList* openList = new NodeList();
    nodesExplored = new NodeList();



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
            std::cout << env[row][col];
            
        }
        std::cout << " " << row << std::endl;
    }

    
    std::cout << "start: " << startNode->getCol() << ", " << startNode->getRow() <<std::endl;
    std::cout << "goal: " << goalNode->getCol() << ", " << goalNode->getRow() <<std::endl;
    std::cout << "openList[0] : (" << openList->getNode(0)->getCol() << ", " << openList->getNode(0)->getRow() << ") " << std::endl;


    std::cout << "Current position:   " << startNode->getCurrentPosition(env) << std::endl;

    std::cout << "Top :     " << startNode->readTopCharacter(env) << std::endl;
    std::cout << "Bottom :  " << startNode->readBottomCharacter(env) << std::endl;
    std::cout << "Left :    " << startNode->readLeftCharacter(env) << std::endl;
    std::cout << "Right :   " << startNode->readRightCharacter(env) << std::endl;


    delete currentNode;
    currentNode = startNode;

    // nodesExplored

    do{

        // reads and checks the TOP
        if(currentNode->readTopCharacter(env) == SYMBOL_EMPTY || currentNode->readTopCharacter(env) == SYMBOL_GOAL){
            bool checker = false;
            // loop to add to open list
            for(int i = 0; i < openList->getLength(); i++){
                // add the element
                if((openList->getLength() == 1) || (!currentNode->equalTo(openList->getNode(i)) && /*!currentNode->equalTo(nodesExplored->getNode(i)) && */checker == false)){
                    openList->addElement(new Node(currentNode->getRow()-1, currentNode->getCol(), currentNode->getDistanceTraveled()+1));
                    //PRINT will remove later
                    std::cout << "Up node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                            openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                            openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;
                    
                    checker = true;
                }
            }
        }

        //reads and checks the BOTTOM
        if(currentNode->readBottomCharacter(env) == SYMBOL_EMPTY || currentNode->readBottomCharacter(env) == SYMBOL_GOAL){
            bool checker = false;
            // loop to add to open list
            for(int i = 0; i < openList->getLength(); i++){
                // add the element
                if((openList->getLength() == 1) || (!currentNode->equalTo(openList->getNode(i)) && /*!currentNode->equalTo(nodesExplored->getNode(i)) && */checker == false)){
                    openList->addElement(new Node(currentNode->getRow()+1, currentNode->getCol(), currentNode->getDistanceTraveled()+1));
                    //PRINT will remove later
                    std::cout << "Down node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                            openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                            openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;
                    
                    checker = true;
                }
            }
        }

        //reads and checks the LEFT
        if(currentNode->readLeftCharacter(env) == SYMBOL_EMPTY || currentNode->readLeftCharacter(env) == SYMBOL_GOAL){
            bool checker = false;
            // loop to add to open list
            for(int i = 0; i < openList->getLength(); i++){
                // add the element
                if((openList->getLength() == 1) || (!currentNode->equalTo(openList->getNode(i)) && /*!currentNode->equalTo(nodesExplored->getNode(i)) && */checker == false)){
                    openList->addElement(new Node(currentNode->getRow(), currentNode->getCol()-1, currentNode->getDistanceTraveled()+1));
                    //PRINT will remove later
                    std::cout << "Left node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                            openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                            openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;
                    
                    checker = true;
                }
            }
        }

        //reads and checks the RIGHT
        if(currentNode->readRightCharacter(env) == SYMBOL_EMPTY || currentNode->readRightCharacter(env) == SYMBOL_GOAL){
            bool checker = false;
            // loop to add to open list
            for(int i = 0; i < openList->getLength(); i++){
                // add the element
                if((openList->getLength() == 1) || (!currentNode->equalTo(openList->getNode(i)) && /*!currentNode->equalTo(nodesExplored->getNode(i)) && */checker == false)){
                    openList->addElement(new Node(currentNode->getRow(), currentNode->getCol()+1, currentNode->getDistanceTraveled()+1));
                    //PRINT will remove later
                    std::cout << "Right node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                            openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                            openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;
                    
                    checker = true;
                }
            }
        }

        

        for(int i = 0; i < openList->getLength(); i++){

            if(openList->getNode(i)->getEstimatedDist2Goal(goalNode) <= currentNode->getEstimatedDist2Goal(goalNode) && 
                !nodesExplored->contains(openList->getNode(i)) ){
                startNode = openList->getNode(i);
            }

        }
        
        nodesExplored->addElement(currentNode);
        std::cout << "Current node: (" << currentNode->getCol() << "," << currentNode->getRow() << "," <<
                                currentNode->getDistanceTraveled() << ") added to closed list" << std::endl;
        
        currentNode = startNode;    
    }while(!nodesExplored->getNode(nodesExplored->getLength() - 1)->equalTo(goalNode) ); 
    std::cout << "You reached there!" << std::endl;

    
        



/*1 Input: E - the environment
2 Input: S - start location of the robot in the environment
3 Input: G - goal location for the robot to get reach
4 Let P be a list of positions the robot can reach, with distances (initially contains S). This is also
called the open-list.
5 Let C be a list of positions the that has already being explored, with distances (initially empty).
This is also called the closed-list.
6 repeat
7 Select the node p from the open-list P that has the smallest estimated distance (see Section 3.2.2)
to goal and, is not in the closed-list C.
8 for Each position q in E that the robot can reach from p do
9 Set the distance_travelled of q to be one more that that of p
10 Add q to open-list P only if it is not already in it.
11 end
12 Add p to closed-list C.
13 until The robot reaches the goal, that is, p == G, or no such position p can be found*/


// if(startNode->readBottomCharacter(env) == '.'){
        //     std::cout << "there is a free space on the bottom" <<std::endl;
        // }
        // if(startNode->readLeftCharacter(env) == '.'){
        //     std::cout << "there is a free space on the left" <<std::endl;
        // }
        // if(startNode->readRightCharacter(env) == '.'){
        //     std::cout << "there is a free space on the Right" <<std::endl;
        // }




}







NodeList* PathSolver::getNodesExplored(){
    //TODO
    
    return nodesExplored;
}


//do later
NodeList* PathSolver::getPath(Env env){
    // TODO
    return nullptr;
}

//-----------------------------