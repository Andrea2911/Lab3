// Lab 3:       The Ladder and Chute Maze Game
// File:        MazeMenu.h
// Description: Class definition of the MazeMenu class.

#ifndef MAZEMENU_H
#define MAZEMENU_H

#include "Node.h"
#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

typedef Node* NodePtr; //represents a pointer to a Node object


// Class: MazeMenu
// Description: This class creates a MazeMenu object which represents
//              the interface for the Ladder and Chute Maze Game.  This class
//              handles the user's inputs and traversal of the maze.
class MazeMenu {
public:
    MazeMenu();
    void welcomeUser();
    void createMaze(ifstream& inStream);
    void setLink(string link, int index, int direction);
    bool traverseMaze();
    string chuteOrLadder(string text);
    string roomChoices(string text);
    int getIndex(string roomName);
    void passMessage();
    void failMessage();
private:
    NodePtr nodes[48];
    NodePtr currentNode;
    string steps;
    int numberMoves;
    string start;
    string end;
};


#endif //MAZEMENU_H
