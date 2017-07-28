// Lab 3:       The Ladder and Chute Maze Game
// File:        Node.h
// Description: Class definition of the Node class.

#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

// Class: Node
// Description: Each Node object represents a point in the maze with five possible
//              connections in the cardinal directions (N,E,S,W) plus a chute/ladder
//              connection.
class Node {
public:
    Node(string newName);
    Node();

    void setNodeName(string newName);
    string getNodeName();
    void attachNewNode(Node *newNode, int direction);
    Node *getAttachedNode(int direction);
    void attachLadderChuteNode(Node *newNode);
    Node *getLadderChuteNode();

private:
    string name;
    Node *attachedNodes[4];
    Node *ladderOrChuteNodes;
};

#endif //NODE_H
