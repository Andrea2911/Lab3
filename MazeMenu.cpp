//
// Created by Andrea Walker on 7/23/17.
//

#include "MazeMenu.h"

void MazeMenu::welcomeUser() {
    cout << string(59, '=') << endl
         << "|           Welcome to the Ladder and Chute Maze           |" << endl
         << string(59, '=') << endl << endl;

    cout << "Enter a filename with a maze: ";
    string filename;
    getline(cin, filename);
    createMaze(filename);
    cout << endl;
}

void MazeMenu::createMaze(string filenameIn) {
    string nodeName, nodeNorth, nodeSouth, nodeEast, nodeWest, chuteOrLadder;
    int numberOfNodes;
    ifstream inStream(filenameIn.c_str());
    for (int i = 0; i < 48; i++) {
        nodes[i] = new Node();
    }
    inStream >> numberOfNodes;
    inStream >> start;
    inStream >> end;
    int nodesIndex = 0;
    while (!inStream.eof() && nodesIndex < 48) {
        string line;
        inStream >> nodeName;
        nodes[nodesIndex]->setNodeName(nodeName);
        inStream >> nodeNorth;
        setLink(nodeNorth, nodesIndex, 0);
        inStream >> nodeEast;
        setLink(nodeEast, nodesIndex, 1);
        inStream >> nodeSouth;
        setLink(nodeSouth, nodesIndex, 2);
        inStream >> nodeWest;
        setLink(nodeWest, nodesIndex, 3);
        inStream >> chuteOrLadder;
        if (chuteOrLadder == "*") {
            nodes[nodesIndex]->attachLadderChuteNode(NULL);
        }
        else {
            char letter = chuteOrLadder[0];
            int letterDif = letter - 65;
            string temp = chuteOrLadder.substr(1, 1);
            stringstream ss(temp);
            int number;// = stoi(temp);
            ss >> number;
            nodes[nodesIndex]->attachLadderChuteNode(nodes[(number - 1) * 8 + letterDif]);
        }
        nodesIndex++;
    }
}

void MazeMenu::setLink(string link, int index, int direction) {
    if (link == "*") {
        nodes[index]->attachNewNode(NULL, direction);
    }
    else {
        char letter = link[0];
        int letterDif = letter - 65;
        string temp = link.substr(1, 1);
        stringstream ss(temp);
        int number;// = stoi(temp);
        ss >> number;
        nodes[index]->attachNewNode(nodes[(number - 1) * 8 + letterDif], direction);
    }
}

bool MazeMenu::traverseMaze() {
    cout << "You can give up at any time be entering 'q' instead of a direction." << endl << endl;
    int startIndex = getIndex(start);
    string message;
    position = nodes[startIndex];
    steps += " " + position->getNodeName();
    while (position->getNodeName() != end) {
        message = "You are currently in Room " + position->getNodeName() + " of the Ladder and Chute Maze, ";
        if (position->getLadderChuteNode() != NULL) {
            message = chuteOrLadder(message);
        }
        else {
            message = roomChoices(message);
        }
        message += " What is your choice? ";
        cout << message;
        char choice;
        cin >> choice;
        cout << endl;
        if (choice == 'N' && position->getAttachedNode(0) != NULL) {
            position = position->getAttachedNode(0);
        }
        else if (choice == 'E' && position->getAttachedNode(1) != NULL) {
            position = position->getAttachedNode(1);
        }
        else if (choice == 'S' && position->getAttachedNode(2) != NULL) {
            position = position->getAttachedNode(2);
        }
        else if (choice == 'W' && position->getAttachedNode(3) != NULL) {
            position = position->getAttachedNode(3);
        }
        else if (choice == 'Q' || choice == 'q') {
            return false;
        }
        else {
            cout << "Invalid input! Please try again." << endl;
            continue;
        }
        numberMoves += 1;
        steps += " " + position->getNodeName();
    }
    //steps += " " + position->getNodeName();
    return true;
}

string MazeMenu::roomChoices(string text) {
    text += "you can go ";
    bool previous = false;
    if (position->getAttachedNode(0) != NULL) {
        text += "North";
        previous = true;
    }
    if (position->getAttachedNode(1) != NULL) {
        if (previous) {
            text += " or East";
            previous = true;
        }
        else {
            text += "East";
            previous = true;
        }
    }
    if (position->getAttachedNode(2) != NULL) {
        if (previous) {
            text += " or South";
            previous = true;
        }
        else {
            text += "South";
            previous = true;
        }
    }
    if (position->getAttachedNode(3) != NULL) {
        if (previous) {
            text += " or West";
        } else {
            text += "West";
        }
    }
    text += ". ";
    return text;

}

string MazeMenu::chuteOrLadder(string text) {
    bool previous = false;
    if (position->getLadderChuteNode() != NULL) {
        text += "and you have taken a\nladder to Room " + position->getLadderChuteNode()->getNodeName() + ", you can go ";
        position = position->getLadderChuteNode();
        if (position->getAttachedNode(0) != NULL) {
            text += "North";
            previous = true;
        }
        if (position->getAttachedNode(1) != NULL) {
            if (previous) {
                text += " or East";
                previous = true;
            }
            else {
                text += "East";
                previous = true;
            }
        }
        if (position->getAttachedNode(2) != NULL) {
            if (previous) {
                text += " or South";
                previous = true;
            }
            else {
                text += "South";
                previous = true;
            }
        }
        if (position->getAttachedNode(3) != NULL) {
            if (previous) {
                text += " or West";
            }
            else {
                text += "West";
            }
        }
        steps += " " + position->getNodeName();
        text += ". ";
    }
    return text;
}

int MazeMenu::getIndex(string roomName) {
    char letter = roomName[0];
    int letterDif = letter - 65;
    string temp = roomName.substr(1, 1);
    stringstream ss(temp);
    int number;// = stoi(temp);
    ss >> number;
    return (number - 1) * 8 + letterDif;
}

void MazeMenu::passMessage() {
    cout << "Congratulations! You have reached the finish point." << endl
         << "You took " + to_string(numberMoves) + " steps." << endl
         << "The nodes you visited are:" + steps << endl;

}

void MazeMenu::failMessage() {
    cout << "Congratulations! You have FAILED to reach the finish point." << endl
         << "You took " + to_string(numberMoves) + " steps." << endl
         << "The nodes you visited are:" + steps << endl;
}


