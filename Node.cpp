#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){  
    
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    int columnArgument;
    int rowArgument;
    
    if(this->col -goal->getCol() < 0){
        columnArgument = ((this->col -goal->getCol())*-1);
    }else{
        columnArgument = (this->col -goal->getCol());
    }

    if(this->row - goal->getRow() < 0){
        rowArgument = ((this->row - goal->getRow())*-1);
    }else{
        rowArgument = (this->row - goal->getRow());
    }

    int manhat_dist = columnArgument + rowArgument;
    return manhat_dist;
}