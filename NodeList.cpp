#include "NodeList.h"
#include <iostream>

Node* node = new Node(0,1,4);

NodeList::NodeList(){
    this->length = 0;
}

NodeList::~NodeList(){
    for (int i=0; i< this->length; i++){
        // delete node objects inside array
        delete (this->nodes)[i];
    }
}

NodeList::NodeList(NodeList& other){
    for(int i =0; i<=other.getLength();i++){
        int otherNodeRow = other.getNode(i)->getRow();
        int otherNodeCol = other.getNode(i)->getCol();
        int otherNodeDist = other.getNode(i)->getDistanceTraveled();
        nodes[i] = new Node(otherNodeRow, otherNodeCol, otherNodeDist);
    }
    this->length = other.getLength();

}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){    
    this->nodes[getLength()] = newPos;
    this->length++;
}

//METHOD THAT CHECKS WHETHER A GIVEN NODE (i.e row and col) IS ALREADY PRESENT WITHIN THE NODELIST. 
//USED IN PATH SOLVER CLASS TO CHECK WHETHER A NODE IS ALREADY PRESENT IN CLOSED LIST
bool NodeList::checkIfContains(int row, int col){
    int count = 0;
    while(count < this->length){
        if(row == this->getNode(count)->getRow() && col == this->getNode(count)->getCol()){
            return true;
        }    
    count++;
    }
    return false;
}

Node* NodeList::getNode(int i){
    // TODO
    return this->nodes[i];
}