// Lab 3:       The Ladder and Chute Maze Game
// File:        UnitTests.cpp
// Description: Driver program to test the Node and MazeMenu objects.
// To run these tests, there must be a Maze1.txt file containing an maze info,

// You can compile these tests by navigating to the directory with:
//      UnitTests.cpp
//      Node.cpp/Node.h
//      MazeMenu.cpp/MazeMenu.h
//      Maze1.txt
// Type:
//      g++ UnitTests.cpp Node.cpp MazeMenu.cpp
// Then type:
// ./testing.out
// to run the tests.

#include "Node.h"
#include "MazeMenu.h"
#include <iostream>
#include <cassert>
using namespace std;

//Node class tests
void getsetNodeNameTest(NodePtr node1);
void attachNewNodeTest(NodePtr node1, NodePtr node2);
void getAttachedNodeTest(NodePtr node1);
void attachLadderChuteNodeTest(NodePtr node1, NodePtr node2);
void getLadderChuteNodeTest(NodePtr node1);

//MazeMenu tests
void welcomeUserCreateMazeTest(MazeMenu& menu);
void traverseMazeTestFail(MazeMenu& menu);
void traverseMazeTestPass(MazeMenu& menu);
void passMessageTest(MazeMenu& menu);
void failMessageTest(MazeMenu& menu);

int main() {
    NodePtr nodeA = new Node();
    NodePtr nodeB = new Node();
    cout << "Testing the Node class:" << endl;
    cout << "Testing Node::setNodeName and Node::getNodeName" << endl;
    getsetNodeNameTest(nodeA);
    cout << "Test setNodeName and getNodeName passed" << endl;
    cout << "Testing attachNewNode" << endl;
    attachNewNodeTest(nodeA, nodeB);
    cout << "Test of attachNewNode passed" << endl;
    cout << "Testing getAttachedNode" << endl;
    getAttachedNodeTest(nodeA);
    cout << "Test of getAttachedNode passed." << endl;
    cout << "Testing attachLadderChuteNode" << endl;
    attachLadderChuteNodeTest(nodeA, nodeB);
    cout << "Test of attachLadderChuteNode passed" << endl;
    cout << "Testing getLadderChuteNode" << endl;
    getLadderChuteNodeTest(nodeA);
    cout << "Test of getLadderChuteNode passed" << endl;

    //MazeMenu class tests
    cout << "The tests for the MazeMenu class require user input to work correctly.\n"
         << "Do you wish to continue? (y/n): " << endl;
    char ans;
    cin >> ans;
    cin.ignore();
    if (ans == 'y') {
        MazeMenu menu1;
        welcomeUserCreateMazeTest(menu1);
        traverseMazeTestFail(menu1);
        traverseMazeTestPass(menu1);
        passMessageTest(menu1);
        failMessageTest(menu1);
    }
    return 0;

}

//Tests the setNodeName and getNodeName methods of the Node class by setting
//and getting the node name and checking if it is equal to the given name
void getsetNodeNameTest(NodePtr node1) {
    node1->setNodeName("A1");
    string name = node1->getNodeName();
    assert(name == "A1");
}

//Tests the attachNewNode method of the Node class by checking that the name of the attached
//Node in the specified direction of the first Node matches the actual Node attached.
void attachNewNodeTest(NodePtr node1, NodePtr node2) {
    node2->setNodeName("A2");
    node1->attachNewNode(node2, 0);
    assert(node1->getAttachedNode(0)->getNodeName() == "A2");
}

//Tests the getAttachedNode method of the Node class by checking that
//node1 has an attached node called "A2"
void getAttachedNodeTest(NodePtr node1) {
    assert(node1->getAttachedNode(0)->getNodeName() == "A2");
}

//Tests the attachLadderChuteNode method of the Node class by attaching a node
//as a ladder/chute node to the first Node and checking the name
void attachLadderChuteNodeTest(NodePtr node1, NodePtr node2) {
    node1->attachLadderChuteNode(node2);
    assert(node1->getLadderChuteNode()->getNodeName() == "A2");
}

//Tests the getLadderChuteNode method of the Node class by checking the name of
//the attached chute/ladder node
void getLadderChuteNodeTest(NodePtr node1) {
    assert(node1->getLadderChuteNode()->getNodeName() == "A2");
}

//Tests the welcomeUser, createMaze, setLink methods of the MazeMenu class. This test checks
//that the user is correctly prompted for a file name and the maze is successfully created.
//This test is verified by the user.
void welcomeUserCreateMazeTest(MazeMenu& menu) {
    cout << "This test tests the welcoeUser, createMaze, and setLink methods of the MazeMEnu"
            "class.  It passes if the user correctly enters a filename and the maze is successfully"
            "created.  If an incorrect filename is entered, the user is prompted to try again." << endl;
    menu.welcomeUser();
}

//Tests the traverseMaze, chuteOrLadder, roomChoices, getIndex methods of the MazeMenu
//class when the user fails to complete the maze.  This test is verified by the user.
void traverseMazeTestFail(MazeMenu& menu) {
    cout << "This test tests the traverseMaze, chuteOrLadder, roomChoices, and getIndex methods"
            "of the Mazemenu class. This test passes if the maze is failed to be completed" << endl;
    bool success = menu.traverseMaze();
    assert(!success);
}

//Tests the traverseMaze, chuteOrLadder, roomChoices, getIndex methods of the MazeMenu
//class when the user completes the maze.  This test is verified by the user.
void traverseMazeTestPass(MazeMenu& menu) {
    cout << "This test tests the traverseMaze, chuteOrLadder, roomChoices, and getIndex methods"
            "of the Mazemenu class. This test passes if the maze is successfully completed" << endl;
    bool success = menu.traverseMaze();
    assert(success);
}

//Tests the passMessage method of the MazeMenu class.  This passes if a congratulatory
//message is displayed along with the number and list of steps.  This test is verified
//by the user.
void passMessageTest(MazeMenu& menu) {
    cout << "This test tests the passMessage method of the MazeMenu class.  This test passes if"
            "a congratulatory message, number and list of steps taken are displayed correctly" << endl;
    menu.passMessage();
}

//Tests the failMessage method of the MazeMenu class.  This passes if a failure
//message is displayed along with the number and list of steps.  This test is verified
//by the user.
void failMessageTest(MazeMenu& menu) {
    cout << "This test tests the passMessage method of the MazeMenu class.  This test passes if"
            "a failing message, number and list of steps taken are displayed correctly" << endl;
    menu.failMessage();
}