//
// Created by Andrea Walker on 7/23/17.
//

#include "MazeMenu.h"

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