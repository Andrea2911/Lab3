//
// Created by Andrea Walker on 7/22/17.
//

#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

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
    bool operator<(const Node& right) const;
    bool operator=(const Node& right) const;

private:
    string name;
    Node *attachedNodes[4];
    Node *ladderOrChuteNodes;
};

#endif //NODE_H
