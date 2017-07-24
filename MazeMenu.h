//
// Created by Andrea Walker on 7/23/17.
//

#ifndef MAZEMENU_H
#define MAZEMENU_H

#include "Node.h"
#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

typedef Node* NodePtr;

class MazeMenu {
public:
    MazeMenu() {steps = ""; numberMoves = 0;};
    void welcomeUser();
    void createMaze(string filenameIn);
    void setLink(string link, int index, int direction);
    bool traverseMaze();
    string chuteOrLadder(string text);
    string roomChoices(string text);
    int getIndex(string roomName);
    void passMessage();
    void failMessage();
private:
    NodePtr nodes[48];
    NodePtr position;
    string steps;
    int numberMoves;
    string start;
    string end;
};


#endif //MAZEMENU_H
