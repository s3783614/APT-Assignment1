#include "PathSolver.h"
#include <iostream>
#include <unistd.h>

PathSolver::PathSolver(){
    // TODO
    // this->nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env){

    
    Node* startNode = new Node(0,0,0);//ini to nullptr
    Node* goalNode = new Node(0,0,0);
    Node* currentNode = new Node(0,0,0);


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
            // std::cout << env[row][col];
        }
        // std::cout << " " << row << std::endl;
    }
    
    // std::cout << "start: " << startNode->getCol() << ", " << startNode->getRow() <<std::endl;
    // std::cout << "goal: " << goalNode->getCol() << ", " << goalNode->getRow() <<std::endl;
    // std::cout << "openList[0] : (" << openList->getNode(0)->getCol() << ", " << openList->getNode(0)->getRow() << ") " << std::endl;

    // std::cout << "Current position:   " << startNode->getCurrentPosition(env) << std::endl;

    // std::cout << "Top :     " << startNode->readTopCharacter(env) << std::endl;
    // std::cout << "Bottom :  " << startNode->readBottomCharacter(env) << std::endl;
    // std::cout << "Left :    " << startNode->readLeftCharacter(env) << std::endl;
    // std::cout << "Right :   " << startNode->readRightCharacter(env) << std::endl;

    // std::cout << openList->getLength() << std::endl;

    delete currentNode;
    currentNode = startNode;

    Node* tempNode = new Node(0,0,10000);
    Node* closest = nullptr;

    do{
    // for(int i = 0)
        //checks the top character to see for free space - then checks for the node in availability
        if((currentNode->readTopCharacter(env) == SYMBOL_EMPTY || currentNode->readTopCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getTopNode(env)) && !closedList->contains(currentNode->getTopNode(env)) )
            {
                Node* tempTopNode = new Node(currentNode->getRow()-1, currentNode->getCol(), currentNode->getDistanceTraveled()+1); 
                openList->addElement(tempTopNode);
                delete tempTopNode;
                // std::cout << "Up node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                //                         openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                //                         openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;

            }
        
        if((currentNode->readBottomCharacter(env) == SYMBOL_EMPTY || currentNode->readBottomCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getBottomNode(env)) && !closedList->contains(currentNode->getBottomNode(env)) )
            {
                Node* tempBottomNode = new Node(currentNode->getRow()+1, currentNode->getCol(), currentNode->getDistanceTraveled()+1);
                openList->addElement(tempBottomNode);
                delete tempBottomNode;
                // std::cout << "Down node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                //                         openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                //                         openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;

            }
        
        if((currentNode->readLeftCharacter(env) == SYMBOL_EMPTY || currentNode->readLeftCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getLeftNode(env)) && !closedList->contains(currentNode->getLeftNode(env)) )
            {
                Node* tempLeftNode = new Node(currentNode->getRow(), currentNode->getCol()-1, currentNode->getDistanceTraveled()+1);
                openList->addElement(tempLeftNode);
                delete tempLeftNode;
                // std::cout << "Left node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                //                         openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                //                         openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;

            }
        
        if((currentNode->readRightCharacter(env) == SYMBOL_EMPTY || currentNode->readRightCharacter(env) == SYMBOL_GOAL) && 
        !openList->contains(currentNode->getRightNode(env)) && !closedList->contains(currentNode->getRightNode(env)) )
            {
                Node* tempRightNode = new Node(currentNode->getRow(), currentNode->getCol()+1, currentNode->getDistanceTraveled()+1); 
                openList->addElement(tempRightNode);
                delete tempRightNode;
                // std::cout << "Right node: (" << openList->getNode(openList->getLength()-1)->getCol() << "," << 
                //                         openList->getNode(openList->getLength()-1)->getRow() << ", " <<
                //                         openList->getNode(openList->getLength()-1)->getDistanceTraveled()  << ") added to open" << std::endl;

            }

        closest = tempNode;
        // std::cout << "ENTERING FOR LOOP" << std::endl;
        for(int i = 0; i < openList->getLength(); i++){

            // std::cout << "openList Node i estimated distance: " << openList->getNode(i)->getEstimatedDist2Goal(goalNode) << std::endl;
            // std::cout << "Closest estimated distance: " << closest->getEstimatedDist2Goal(goalNode) << std::endl;
            // std::cout << "openList node i NOT explored: " << !nodesExplored->contains(*(openList->getNode(i))) << std::endl;
            // std::cout << "openList node i NOT equal to current: " << !openList->getNode(i)->equalTo(*currentNode) << std::endl;
            // std::cout << "-------------------------" << std::endl;

            if(openList->getNode(i)->getEstimatedDist2Goal(goalNode) < closest->getEstimatedDist2Goal(goalNode) &&
              !closedList->contains(*(openList->getNode(i))) && !openList->getNode(i)->equalTo(*currentNode) ){
                // std::cout << "Closest node distance now set to " << openList->getNode(i)->getEstimatedDist2Goal(goalNode) << std::endl;
                closest = openList->getNode(i);
                // std::cout << "Closest node: (" << closest->getCol()  << ", "<< closest->getRow() << ", " << closest->getDistanceTraveled() << ") changed" << std::endl;
            }

        }
        
        closedList->addElement(currentNode);
        // std::cout << "Current node: (" << currentNode->getCol() << "," << currentNode->getRow() << "," <<
        //                         currentNode->getDistanceTraveled() << ") added to closed list" << std::endl;
        
        currentNode = closest;
        // printMovement(env, *currentNode);
        
        // usleep(100000);
    }while(!closedList->getNode(closedList->getLength() - 1)->equalTo(*goalNode) && 
           openList->getLength() != closedList->getLength());
    
    // printSolution(env, closedList);

    //MAP OUT WHAT IS HAPPENING CAUSE THIS COON IS JUMPING PLACES THAT HE IS NOT MEANT TO BE GOING 

    // std::cout << "You reached there!" << std::endl;

    //just for inspection purposes
    /*std::cout << "final position: " <<  closedList->getNode(closedList->getLength()-1)->getCol() << "," << 
                                        closedList->getNode(closedList->getLength()-1)->getRow() << ", " <<
                                        closedList->getNode(closedList->getLength()-1)->getDistanceTraveled() << std::endl;
    std::cout << "goal: " << goalNode->getCol() << ", " << goalNode->getRow() <<std::endl;*/

    nodesExplored = new NodeList(*closedList);

    delete goalNode;
    delete startNode;
    // delete currentNode;
    delete tempNode;
    // delete closest;

    delete openList;
    delete closedList;

}

NodeList* PathSolver::getNodesExplored(){
    
    // return nodesExplored;
    return new NodeList(*nodesExplored);
    
}

//do later
NodeList* PathSolver::getPath(Env env){
    // TODO

    NodeList* finalPath = new NodeList();
    //declared this cause i want it to start after this
    Node* goal = nodesExplored->getNode(nodesExplored->getLength()-1);

    // std::cout << "goal Node: " << goal->getRow() << ", " <<goal->getCol() << ", " << goal->getDistanceTraveled() << std::endl;

    // nodesExplored->getNode(i) && > 0 cause u need to display start
    for(int i = nodesExplored->getLength()-1; i > 0; i--){

        // std::cout << "Node [ " << i << " ]: (" << nodesExplored->getNode(i)->getRow() << ", " <<nodesExplored->getNode(i)->getCol() 
        //                                         << ", " << nodesExplored->getNode(i)->getDistanceTraveled() << " )" << std::endl;

        if(nodesExplored->getNode(i)->getDistanceTraveled() == (goal->getDistanceTraveled()-1) ){

            if( goal->getTopNode(env).equalTo(*(nodesExplored->getNode(i)))    ||
                goal->getBottomNode(env).equalTo(*(nodesExplored->getNode(i))) ||
                goal->getLeftNode(env).equalTo(*(nodesExplored->getNode(i)))   ||
                goal->getRightNode(env).equalTo(*(nodesExplored->getNode(i)))  ){

                // std::cout << "goal Node before: " << goal->getRow() << ", " <<goal->getCol() << ", " << goal->getDistanceTraveled() << std::endl;
                goal = nodesExplored->getNode(i);
                // std::cout << "goal Node after: " << goal->getRow() << ", " <<goal->getCol() << ", " << goal->getDistanceTraveled() << std::endl;
                // std::cout << std::endl;

                finalPath->addElement(goal);
                // std::cout << "finalPath [" << i << "] : " << finalPath->getNode(i)->getRow() << ", " << finalPath->getNode(i)->getCol() <<
                //              ", " << finalPath->getNode(i)->getDistanceTraveled() << "added to  finalPath" << std::endl;


                //Print debugging information
                // printMovement(env,*goal);
                // std::string uslessElement = "";
                // std::cout << uslessElement;
            }

        }
        // 1800640886 -- media super
    }

    //template inCase
    // for(int i = 0; i < finalPath->getLength(); i++){

    // }

    //prints all the nodes in the final path array
    // for(int i = 0; i < finalPath->getLength(); i++){
    //         std::cout << "finalPath [" << i << "] : (" << finalPath->getNode(i)->getRow() << ", " << finalPath->getNode(i)->getCol() <<
    //                          ", " << finalPath->getNode(i)->getDistanceTraveled() << ") added to  finalPath" << std::endl;
    // }

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