#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    this->nodenext = new NodeList(); //OPEN-LIST
    this->nodesExplored = new NodeList(); //CLOSED-LIST
}

PathSolver::~PathSolver(){
    delete nodenext;
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env, int env_row, int env_col){

    //ADDING START NODE TO OPEN-LIST    
    nodenext->addElement(findsymbolInEnv(env,SYMBOL_START, env_row, env_col));
    
    //THIS LOOP WILL GO THROUGH EACH NODE IN OPEN LIST AND FIND ADJACENT NODES, THAT ARE NOT PRESENT IN THE CLOSED LIST
    for(int x = 0; x<nodenext->getLength();x++){
        findAdjacentNodes(nodenext->getNode(x),env, env_row, env_col);
    }

}

//WILL FIND ANY SYMBOL IN THE ENVIRONMENT. PRIMARILY USED TO FIND THE START NODE AND GOAL NODE.
//THE DISTANCE TRAVELLED IS HARDCODED TO 0, WHICH REMAINS TRUE FOR START NODE. HOWEVER, FOR GOAL NODE, IT MUST BE UPDATED ON USE.     
Node* PathSolver::findsymbolInEnv(Env env, char symbol, int env_row, int env_col){
    Node* tmpNode;

    for(int x=0; x < env_row; x++){
        for (int y = 0; y<env_col; y++){
            if(env[x][y] == symbol){
                tmpNode = new Node(x,y,0);
            }
        }
    }
    return tmpNode;
}

/*
THIS METHOD WILL FIND ADJACENT NODES OF A GIVEN NODE. IF THE ADJACENT NODE FULFILLS REQUIREMENTS, IT WILL BE ADDED TO THE OPEN LIST. THE PASSED
NODE WILL BE ADDED TO THE CLOSED-LIST, AS IT HAS BEEN EXPLORED*/
void PathSolver::findAdjacentNodes(Node* node, Env env, int env_row, int env_col){
    int row = node->getRow(); //ROW OF GIVEN NODE
    int col =node->getCol(); //COLUMN OF GIVEN NODE
    int distance = node->getDistanceTraveled(); //DISTANCE TRAVELLED OF GIVEN NODE

    Node* tempNode;

    if(env[row][col] == SYMBOL_GOAL){ //IF WE REACH GOAL NODE, THERE IS NO NEED TO FIND ADJACENT NODES
        nodesExplored->addElement(new Node(row,col,distance));
    }
    else{ //IF THE CURRENT NODE IS NOT THE GOAL NODE, RELEVANT ADJACENT NODES MUST BE ADDED TO THE OPEN LIST

        //CHECK ADJACENT NODES. IF IT IS EITHER AN EMPTY OR GOAL NODE, IT WILL BE ADDED TO THE OPEN-LIST
        if(row - 1 >= 0){
            if((env[row-1][col] == SYMBOL_EMPTY || env[row-1][col] == SYMBOL_GOAL) && !(nodesExplored->checkIfContains(row-1,col))){
                tempNode = new Node (row-1,col,distance+1);
                nodenext->addElement(tempNode);
            }; 
        }
        
        if(row + 1 < env_row){
            if((env[row+1][col] == SYMBOL_EMPTY || env[row+1][col] == SYMBOL_GOAL) && !(nodesExplored->checkIfContains(row+1,col))){
                tempNode = new Node (row+1,col,distance+1);
                nodenext->addElement(tempNode);
            };

        }
        
        if (col + 1 < env_col){
            if((env[row][col+1] == SYMBOL_EMPTY || env[row][col+1] == SYMBOL_GOAL) && !(nodesExplored->checkIfContains(row,col+1))){
                tempNode = new Node (row,col+1,distance+1);
                nodenext->addElement(tempNode);
            };
        }
        
        if(col + 1 >= 0){
            if((env[row][col-1] == SYMBOL_EMPTY || env[row][col-1] == SYMBOL_GOAL) && !(nodesExplored->checkIfContains(row,col-1))){
                tempNode = new Node (row,col-1,distance+1);
                nodenext->addElement(tempNode);
            };
        }
        
        nodesExplored->addElement(new Node(row,col,distance)); //FINALLY THE GIVEN NODE IS ADDED TO THE CLOSED LIST, ONCE IT IS EXPLORED.
    }
    
}    


NodeList* PathSolver::getNodesExplored(){
    return this->nodesExplored;
}

NodeList* PathSolver::getPath(Env env, int env_row, int env_col){
    // TODO

    NodeList* templist = new NodeList(); //Stores backtrack path from Goal to Start
    NodeList* templist_reversed = new NodeList(); //Will store reversed tempList, to be returned since we need a path from START to GOAL 
    
    Node* goal_node = findsymbolInEnv(env, SYMBOL_GOAL, env_row, env_col); //THE GOAL NODE HERE, HAS INCORRECT VALUE FOR DISTANCE TRAVELLED.

    //UPDATE THE goal_node TO THE NODE IN CLOSED LIST, HAVING THE SAME ROW AND COLUMN, TO CORRECT THE distance_travelled VALUE 
    for(int i = 0; i< nodesExplored->getLength(); i++){
        if(nodesExplored->getNode(i)->getRow() == goal_node->getRow() && nodesExplored->getNode(i)->getCol() == goal_node->getCol()){
            
            goal_node = nodesExplored->getNode(i);
        }
    }
    
    templist->addElement(goal_node); //ADD THE GOAL NODE TO THE TEMP LIST. NOW, WE NEED TO BACK TRACK TO THE START NODE.

    
    int goal_row = goal_node->getRow();
    int goal_col = goal_node->getCol();
    int goal_dist = goal_node->getDistanceTraveled();

    for(int x = 0; x < templist->getLength(); x++){ //A LOOP RUNNING THROUGH TEMP_LIST TO FIND THE NEXT NODE TO BE ADDED TO TEMP_LIST

        int goal_row = templist->getNode(x)->getRow();
        int goal_col = templist->getNode(x)->getCol();
        int goal_dist = templist->getNode(x)->getDistanceTraveled();

         /*LOOP THROUGH THE CLOSED LIST TO FIND AN ADJACENT NODE OF THE CURRENT GOAL NODE, 
           WHICH HAS DISTANCE TRAVELLED, ONE LESS THAN GOAL NODE'S*/
        for(int i = 0; i<nodesExplored->getLength(); i++){  

            //IN CASE, ROW IS SAME, WE NEED TO CHECK WHETHER THE COLUMN DIFFERS BY 1
            if(nodesExplored->getNode(i)->getRow() == goal_row){
                //IF COLUMN DIFFERS BY 1, WE NEED TO CHECK WHETHER DISTANCE TRAVELLED IS 1 LESS THAN GOAL NODE
                if(nodesExplored->getNode(i)->getCol() == goal_col+1 || nodesExplored->getNode(i)->getCol() == goal_col-1){
                    //IF DISTANCE TRAVELLED IS ONE LESS THAN GOAL NODE, WE HAVE FOUND THE NEXT NODE IN PATH, AND IT MUST BE ADDED TO TEMP LIST.
                    if(nodesExplored->getNode(i)->getDistanceTraveled() == goal_dist-1 ){
                        templist->addElement(nodesExplored->getNode(i));
                    }
                }
            }

            //IN CASE, COLUMN IS SAME, WE NEED TO CHECK WHETHER THE ROW DIFFERS BY 1
            if(nodesExplored->getNode(i)->getCol() == goal_col){
                //IF ROW DIFFERS BY 1, WE NEED TO CHECK WHETHER DISTANCE TRAVELLED IS 1 LESS THAN GOAL NODE
                if(nodesExplored->getNode(i)->getRow() == goal_row+1 || nodesExplored->getNode(i)->getRow() == goal_row-1){
                    //IF DISTANCE TRAVELLED IS ONE LESS THAN GOAL NODE, WE HAVE FOUND THE NEXT NODE IN PATH, AND IT MUST BE ADDED TO TEMP LIST
                    if(nodesExplored->getNode(i)->getDistanceTraveled() == goal_dist-1 ){
                        templist->addElement(nodesExplored->getNode(i));
                    }
                
                }   
            }

        }

    }

    //TEMP LIST STORES THE BACK-TRACKED PATH FROM GOAL NODE TO START NODE. WE MUST REVERSE THE LIST, TO FIND PATH FROM START TO GOAL.
    for(int i=templist->getLength()-1; i>=0; i--){
        templist_reversed->addElement(templist->getNode(i));
    }
    
    /*I tried to delete the templist after usage, to remove memory leaks. However, deleting the templist was causing an error: 
    'free(): double free detected in tcache 2'*/
    //delete templist;        
    
    
    return templist_reversed; //RETURN PATH FROM START TO GOAL
}

