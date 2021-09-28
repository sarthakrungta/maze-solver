#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"


/*
****CODE DESCRIPTION****
I have tried to implement the forward search and back-tracking algorithms as described in the assignment. 

Firstly, the environment is read using the readEnvStdin() function. Until Milestone 3, the loop would run through 20 rows and 20 columns, taking input for each node. 
For Milestone 4, I first counted the number of rows and columns in the input, using '\n' as the indicator for the next row. Then, I created a similar loop. 

The forward search algorithm would update the closed list with every possible empty node. 
The getPath() method would analyz the closed-list, find the goal node, and then find an adjacent node with a 1 less distance travelled. This would
repeat until Start node is reached, and a path is returned, as a list of nodes. 

To print back the response, we replace the nodes in the solution, with an appropriate path indicator ('<,>,^,v') depending on the next node of the solution

****ISSUES ENCOUNTERED****
I could not successfully implement a method which picks the node from the open-list with the least distance to goal, and then finds the adjacent nodes.
Instead, my forwardSearch algorithm checks whether the node in open-list is included in the closed-list. If not, it finds the adjacent nodes, and adds them to the open-list.

Removing memory leaks proved to be a difficult task. Initially, I was losing 12980 bytes of memory in leaks. I reduced this to 12 bytes, but that was causing
a different set of errors. (P.S details at (PathSolver.cpp:163)). 

Deleting explored position was leading to a segmentation error, even though the variable is initialized and set to nodesExplored

****INTERESTING INSIGHT****
I tested the program with multiple Goal nodes in Sample03. Interestingly, the program shows the path to the farthest Goal node possible. 
I believe, since the farthest goal node would be the last to be added to the closed-list, it shows the path from start to that goal node.
*/


// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);
Env readDynamicEnv();

Env make_env(int rows, int cols);

int env_rows; //GLOBAL VARIABLE TO STORE THE NUMBER OF ROWS IN THE DYNAMIC ENVIRONMENT
int env_cols; //GLOBAL VARIABLE TO STORE THE NUMBER OF COLUMNS IN THE DYNAMIC ENVIRONMENT

int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    /*std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;*/

    // Load Environment 
    Env env;
    env = readDynamicEnv();
    

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env, env_rows, env_cols);

    

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env, env_rows, env_cols);

    printEnvStdout(env, solution);

    delete pathSolver;
    //delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
    char c;
    std::cin>>c;
}

//THIS METHOD WILL COUNT THE NUMBER OF ROWS AND COLUMNS IN INPUT. IT ALSO POPULATES THE DYNAMIC ENVIRONMENT WITH THE INPUT
Env readDynamicEnv(){

    Env env = nullptr; 
    int x = 0; //Counter for while loop
    int rows = 0; //rows in environment
    int cols = 0; //columns in environment
    std::string environemnt_string; //Will store all symbols in the environment as a string
    
    //Will read input, and count the number of rows and columns
    while(!std::cin.eof()){ //While end of file is not reached
        char c;
        std::cin.get(c); //get each individual character 
        cols++; //update the column with each character input
        if(c == '\n'){ //when we reach line break, the row is updated by 1.
            rows++;
            cols--; //we deduct 1 from the column, since '\n' is also treated as a character and updates the column.
        }else{
            if(!isspace(c)){ //We also make sure that the charcter is not a white space, and add it to the environment string
                environemnt_string = environemnt_string + c;
            }
        }
        ++x;
    }
    environemnt_string.pop_back(); //Upon testing, I found that the environment string always contains one extra symbol. 
                                   //Thus, I delete the last elemnt in the string after its populated. We also do this for the columns later
    
    rows = rows+1; //The last row does not have a line break, and therefore we must add one row manually
    cols = (cols - 1)/rows; //We divide the column count by the number of rows, since we add columns for each symbol, in each row!

    //Set the global variables for rows and columns
    env_rows = rows; 
    env_cols = cols;

    env = make_env(rows, cols); //Make an Env variable with the dynamic rows and columns

    //Populate the environment
    int strPos = 0;
    for(int i = 0; i< env_rows; i++){
        for(int x = 0; x < env_cols; x++){
            env[i][x] = environemnt_string[strPos];
            strPos++;
        }
    }
    return env;
}

void printEnvStdout(Env env, NodeList* solution) {
    //Replace each node in the environment, present in the solution, with an appropriate directional symbol
    for(int i = 1; i< solution->getLength()-1; i++){
        Node* pathPoint = solution->getNode(i);
        //We will check the next node in the solution, and replace the current node with a directional support leading to the next node.
        if(solution->getNode(i+1)->getRow() == solution->getNode(i)->getRow() - 1){
            env[pathPoint->getRow()][pathPoint->getCol()] = '^';
        }
        else if(solution->getNode(i+1)->getRow() == solution->getNode(i)->getRow() + 1){
            env[pathPoint->getRow()][pathPoint->getCol()] = 'v';
        }
        else if(solution->getNode(i+1)->getCol() == solution->getNode(i)->getCol() + 1){
            env[pathPoint->getRow()][pathPoint->getCol()] = '>';
        }
        else if(solution->getNode(i+1)->getCol() == solution->getNode(i)->getCol() - 1){
            env[pathPoint->getRow()][pathPoint->getCol()] = '<';
        }
        
        
    }

    //Print the Environment with the replaced path
    for(int x=0; x < env_rows; x++){

        for (int y = 0; y<env_cols; y++){
            std::cout<<env[x][y];
        }
        std::cout<<std::endl;
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

Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }

   return env;
}

void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
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
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
    for (int i = 0; i < nodeList->getLength(); i++)
    {
        Node* temp_node = nodeList->getNode(i);
        std::cout << temp_node->getRow() << ",";
        std::cout << temp_node->getCol() << ",";
        std::cout << temp_node->getDistanceTraveled() << std::endl;

        delete temp_node;
    }
    
}