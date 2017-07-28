// Lab 3:       The Ladder and Chute Maze Game
// File:        Node.cpp
// Description: Implementation of the Node class.

#include "Node.h"

// Function:    Node constructor
// Description: Empty Node constructor
Node::Node() {

}

// Function:    Node constructor
// Description: Assigns the given newName to the field name.
Node::Node(string newName) {
    name = newName;
}
// Function:    setNodeName
// Inputs:      The desired name for a Node object
// Description: Assigns the given newName to the field name.
void Node::setNodeName(string newName) {
    name = newName;
}

// Function:    getNodeName
// Outputs:     The name of the Node
// Description: Returns the name of the current Node when called.
string Node::getNodeName() {
    return name;
}

// Function:    attachNewNode
// Inputs:      A pointer to a new node, and the direction it should be in
// Description: Attaches a pointer to a new Node in the desired direction
//              for the current node
void Node::attachNewNode(Node *newNode, int direction) {
    attachedNodes[direction] = newNode;
}

// Function:    getAttachedNode
// Inputs:      The direction of a node, represented as an integer
// Outputs:     A pointer to a Node attached to this Node, in the specified direction
// Description: Finds and returns an attached Node in the specified direction
Node *Node::getAttachedNode(int direction) {
    return attachedNodes[direction];
}

// Function:    attachLadderChuteNode
// Inputs:      A pointer to a new ladder/chute node
// Description: Attaches a pointer to a ladder/chute Node for the current node
void Node::attachLadderChuteNode(Node *newNode) {
    ladderOrChuteNodes = newNode;
}

// Function:    getLadderChuteNode
// Outputs:     A point to the ladder/chute Node attached to this Node
// Description: Finds and returns the ladder/chute Node of the current Node
Node *Node::getLadderChuteNode() {
    return ladderOrChuteNodes;
}
