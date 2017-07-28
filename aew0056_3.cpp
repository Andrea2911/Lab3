// Lab 3:       The Ladder and Chute Maze Game
// Name:        Andrea E. Walker
// Class:       COMP 2710 Section 2
// Date:        July 28, 2017
// E-Mail:      aew0056@auburn.edu
// User-ID:     aew0056
// Filename:    aew0056_3.cpp
//
// Compiling instructions:
// From the terminal, navigate to the directory where the following files are located:
//   aew0056_2.cpp
//   MazeMenu.cpp/MazeMenu.h
//   Node.cpp/Node.h
//   Any maze files you may want to use, such as:
//   Maze1.txt, Maze2.txt, Maze3.txt
//
// To compile this program, type:
// "g++ aew0056_3.cpp Node.cpp MazeMenu.cpp -o aew0056_3.out"
// and hit enter. Once the program compiles, type "./aew0056_3.out" and the program will
// begin, prompting the user to enter a maze filename.
//
// Description: This program is a simple ladder and chute maze game. Once
//              a user enters a maze filename, the maze is created and the
//              user is prompted to choose any of the available directions.
//              If the user reaches the end of the maze, they are congraguated.
//              If the user gives up, they can enter 'q' at any time to quit
//              and see a failing message.



#include "MazeMenu.h"

// Function: main
// Description: Instantiates a MazeMenu object, welcomes the user, traverses the maze,
// and displays a pass or fail message dependent on the successful traversal of the maze..
int main() {
    MazeMenu menu;
    menu.welcomeUser();
    bool success = menu.traverseMaze();
    if (success) {
        menu.passMessage();
    }
    else {
        menu.failMessage();
    }
    return 0;
}