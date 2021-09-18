//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

/** This is a basic game I made while following a tutorial
 *  Its hardcoded to run at 144fps 1080p, but that can be changed
 *  SFML library is needed in order to compile
 * */

#include <iostream>
#include "game.h"

int main(){
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));
    // Init Game engine
    Game game;

    // Game loop
    while (game.running()){
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}