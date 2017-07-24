//
// Created by Andrea Walker on 7/22/17.
//

#include "Node.h"

Node::Node() {

}

Node::Node(string newName) {
    name = newName;
}

void Node::setNodeName(string newName) {
    name = newName;
}

string Node::getNodeName() {
    return name;
}

void Node::attachNewNode(Node *newNode, int direction) {
    attachedNodes[direction] = newNode;
}

Node *Node::getAttachedNode(int direction) {
    return attachedNodes[direction];
}

void Node::attachLadderChuteNode(Node *newNode) {
    ladderOrChuteNodes = newNode;
}

Node *Node::getLadderChuteNode() {
    return ladderOrChuteNodes;
}

bool Node::operator<(const Node &right) const {
    return name < right.name;
}

bool Node::operator=(const Node &right) const {
    return name == right.name;
}