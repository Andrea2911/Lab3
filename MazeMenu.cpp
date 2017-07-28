// Lab 3:       The Ladder and Chute Maze Game
// File:        MazeMenu.cpp
// Description: Implementation of the MazeMenu class.

#include "MazeMenu.h"

// Function:    MazeMenu constructor
// Description: Initializes some members of the MazeMenu class.
MazeMenu::MazeMenu() {
    steps = "";
    numberMoves = 0;
    start = "A1";
    end = "H6";
}

// Function:    welcomeUser
// Description: Welcomes the user fo the maze game, and prompts the user for a
//              filename.  If an invalid filename is given, the user is prompted
//              to try again.  When a valid filename is given, the maze is created.
void MazeMenu::welcomeUser() {
    cout << string(59, '=') << endl
         << "|           Welcome to the Ladder and Chute Maze           |" << endl
         << string(59, '=') << endl << endl;
    ifstream instream; //for file reading
    bool validFile = false;
    //given filename assumed to be invalid until proven otherwise
    while (!validFile) {
        cout << "Enter a filename with a maze: ";
        string filename;
        getline(cin, filename);
        cout << endl;
        instream.open(filename.c_str()); //try opening the file
        if (!instream.fail()) { //if file open successful, program may proceed
            validFile = true;
        }
        else {
            cout << "That file does not exist! Try another file." << endl;
        }
    }
    createMaze(instream); //creates the graphical representation of the maze
}

// Function:    createMaze
// Inputs:      Reference to an ifstream object for file reading
// Description: Reads the maze file, and fills the array "nodes" with all of the Nodes
//              and their attached Nodes from the file.
void MazeMenu::createMaze(ifstream& inStream) {
    string nodeName, nodeNorth, nodeSouth, nodeEast, nodeWest, chuteOrLadder;
    //file the array nodes with empty Nodes
    for (int i = 0; i < 48; i++) {
        nodes[i] = new Node();
    }
    int nodesIndex = 0;
    //read the entire file
    while (!inStream.eof() && nodesIndex < 48) {
        inStream >> nodeName; //the name of a Node
        nodes[nodesIndex]->setNodeName(nodeName);
        inStream >> nodeNorth; //Node to the north
        setLink(nodeNorth, nodesIndex, 0);
        inStream >> nodeEast; //Node to the east
        setLink(nodeEast, nodesIndex, 1);
        inStream >> nodeSouth; //Node to the south
        setLink(nodeSouth, nodesIndex, 2);
        inStream >> nodeWest; //Node to the west
        setLink(nodeWest, nodesIndex, 3);
        inStream >> chuteOrLadder;
        //if no chute/ladder node, set it to NULL
        if (chuteOrLadder == "*") {
            nodes[nodesIndex]->attachLadderChuteNode(NULL);
        }
        else {
            char letter = chuteOrLadder[0]; //the first char (the letter) of a Node
            int letterDif = letter - 65; //The difference between the letter and 'A'
            string temp = chuteOrLadder.substr(1, 1); //temp string of the number of a Node
            stringstream ss(temp);
            int number;
            ss >> number; //places the number as an integer
            //calculates which index in nodes the chute/ladder node belongs to
            nodes[nodesIndex]->attachLadderChuteNode(nodes[(number - 1) * 8 + letterDif]);
        }
        nodesIndex++; //move on to the next Node
    }
    inStream.close();
}

// Function:    setLink
// Inputs:      the new link node name, the index of the current Node, and the direction of the link
// Outputs:     True if the username is already a friend
// Description: Determines whether a given name is a friend of the User.
void MazeMenu::setLink(string link, int index, int direction) {
    if (link == "*") {
        nodes[index]->attachNewNode(NULL, direction);
    }
    else {
        char letter = link[0]; //the first char (the letter) of a Node name
        int letterDif = letter - 65; //The difference between the letter and 'A'
        string temp = link.substr(1, 1); //temp string of the number of a Node
        stringstream ss(temp);
        int number;
        ss >> number; //places the number as an int
        //calculates which index in nodes the attached node belongs to
        nodes[index]->attachNewNode(nodes[(number - 1) * 8 + letterDif], direction);
    }
}

// Function:    traverseMaze
// Outputs:     True if the user successfully traverses the maze
// Description: Handles the user input for traversing the maze and returns true if the user
//              successfully traverses the maze.
bool MazeMenu::traverseMaze() {
    cout << "You can give up at any time be entering 'q' instead of a direction." << endl << endl;
    int startIndex = getIndex(start); //find the index in nodes of the start Node
    string message;
    position = nodes[startIndex]; //pointer to the user's current position, beginning at start
    steps += " " + position->getNodeName(); //add to the steps the user has taken
    while (position->getNodeName() != end) {
        message = "You are currently in Room " + position->getNodeName() + " of the Ladder and Chute Maze, ";
        //moves the user if there is a chute/ladder in the new position
        if (position->getLadderChuteNode() != NULL) {
            message = chuteOrLadder(message);
        }
        else {
            message = roomChoices(message);
        }
        message += " What is your choice? ";
        cout << message;
        char choice;
        cin >> choice;//read the user's choice
        cout << endl;
        //check which direction the user chose
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
        //allows the user to quit
        else if (choice == 'Q' || choice == 'q') {
            return false;
        }
        else {
            cout << "Invalid input! Please try again." << endl;
            continue;
        }
        numberMoves += 1; //increment number of moves
        steps += " " + position->getNodeName();
    }
    return true;
}

// Function:    roomChoices
// Inputs:      a string that will eventually be displayed to the user
// Outputs:     an edited version of the original text
// Description: Determines the directions a user can go within a room
string MazeMenu::roomChoices(string text) {
    text += "you can go ";
    bool previous = false;
    //find the avaiable directions
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

// Function:    chuteOrLadder
// Inputs:      a string that will eventually be displayed to the user
// Outputs:     an edited version of the text plus the available directions
// Description: Moves the user to the node attached to a chute/ladder and determines
//              which direction a user can go
string MazeMenu::chuteOrLadder(string text) {
    if (position->getLadderChuteNode() != NULL) {
        string name1 = position->getNodeName().substr(1,1);
        string name2 = position->getLadderChuteNode()->getNodeName().substr(1,1);
        int comp = name1.compare(name2); //decides if the user is encountering a chute or ladder
        if (comp > 0) {
            text += "and you have taken a\nchute to Room " + position->getLadderChuteNode()->getNodeName() + ", ";
        }
        else {
            text += "and you have taken a\nladder to Room " + position->getLadderChuteNode()->getNodeName() + ", ";
        }
        position = position->getLadderChuteNode();
        text = roomChoices(text); //get the room choices
        steps += " " + position->getNodeName();
    }
    return text;
}

// Function:    getIndex
// Inputs:      the name of a room in the maze
// Outputs:     index of the name of a room in the array nodes
// Description: Finds the index of a given name of a room in the array of nodes.
int MazeMenu::getIndex(string roomName) {
    char letter = roomName[0];
    int letterDif = letter - 65;
    string temp = roomName.substr(1, 1);
    stringstream ss(temp);
    int number;
    ss >> number;
    //calculates the position of a node name in the array of Nodes
    return (number - 1) * 8 + letterDif;
}

// Function:    passMessage
// Description: Displays a message congratulating the user on completing the maze,
//              as well as a list of the steps the user took and the number of steps
//              they took.
void MazeMenu::passMessage() {
    ostringstream sstream;
    sstream << numberMoves;
    string moves = sstream.str();
    cout << "Congratulations! You have reached the finish point." << endl
         << "You took " + moves + " steps." << endl
         << "The nodes you visited are:" + steps << endl;

}

// Function:    failMessage
// Description: Displays a message congratulating the user on FAILING the maze,
//              as well as a list of the steps the user took and the number of steps
//              they took.
void MazeMenu::failMessage() {
    ostringstream sstream;
    sstream << numberMoves;
    string moves = sstream.str();
    cout << "Congratulations! You have FAILED to reach the finish point." << endl
         << "You took " + moves + " steps." << endl
         << "The nodes you visited are:" + steps << endl;
}


