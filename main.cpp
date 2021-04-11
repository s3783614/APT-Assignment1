/*
For this assignment I believe that I have successfully completed milestone 1,2,3
I had a bit of difficulty when I initially started the assignment, but one of the
lecturers mentioned it would be a good place to start by reading one node up,
left, down and right. Using that advice I went on to scan the entire environment
using a few extra methods I wrote for the node class. Another problem 
encountered was acutally finding the shortest distance node in the openlist but 
that was resolved through simply resetting a temporary node which had to big a 
distance stored within it. Similarly milestone 3 seemed a bit difficulty at 
start but it was just a matter of reading the assignment specifications as it 
started that all we had to do was modify the maze directly so replace the '.' 
with an UP, DOWN, LEFT, or RIGHT arrowhead.
*/
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

enum {
    UPWARD = '^',
    DOWNWARD = 'V',
    LEFTWARD = '<',
    RIGHTWARD = '>'
};

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    /*
    * THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    * AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    * AS YOU GO ALONG.
    * COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    * std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << 
    *                                                                 std::endl;
    * testNode();
    * testNodeList();
    * std::cout << "DONE TESTING" << std::endl << std::endl;
    */

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
    //TODO 
    for(int row = 0; row < ENV_DIM; row++){
        for(int col = 0; col < ENV_DIM; col++){
            std::cin >> env[row][col];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    //TODO

    for(int i = solution->getLength()-1; i >= 0; i--){


        Node* current = solution->getNode(i);        

        if( ( (current->readTopCharacter(env) == SYMBOL_EMPTY)   ||
              (current->readTopCharacter(env) == SYMBOL_GOAL) )  && 
            (solution->contains(current->getTopNode(env)) || 
            (current->readTopCharacter(env) == SYMBOL_GOAL) ) )
        {
            env[current->getRow()][current->getCol()] = UPWARD;
        }

        if( ( (current->readBottomCharacter(env) == SYMBOL_EMPTY) || 
              (current->readBottomCharacter(env) == SYMBOL_GOAL) )&& 
            (solution->contains(current->getBottomNode(env)) ||
            (current->readBottomCharacter(env) == SYMBOL_GOAL) ) )
        {
            env[current->getRow()][current->getCol()] = DOWNWARD;
        }

        if( ( (current->readLeftCharacter(env) == SYMBOL_EMPTY) ||
              (current->readLeftCharacter(env) == SYMBOL_GOAL) )&&
            (solution->contains(current->getLeftNode(env)) ||
            (current->readLeftCharacter(env) == SYMBOL_GOAL) ) )
        {
            env[current->getRow()][current->getCol()] = LEFTWARD;
        }

        if( ( (current->readRightCharacter(env) == SYMBOL_EMPTY) ||
              (current->readRightCharacter(env) == SYMBOL_GOAL) )&&
            (solution->contains(current->getRightNode(env)) ||
            (current->readRightCharacter(env) == SYMBOL_GOAL) ) )
        {
            env[current->getRow()][current->getCol()] = RIGHTWARD;
        }

    }

    //For printing the solution
    for(int row = 0; row < ENV_DIM; row++){
        
        for(int col = 0; col < ENV_DIM; col++){

            std::cout << env[row][col];
            
        }

        if(row != ENV_DIM - 1 )
        {
            std::cout << std::endl;
        }
        
    }

}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << 
                                                                    std::endl;
}