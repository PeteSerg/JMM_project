// This does not need to be on the main branch, and can be deleted

//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

// x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/home/xnely/Downloads/SFML-2.5.1/include/
// x86_64-w64-mingw32-g++ -DSFML_STATIC -I/home/xnely/Downloads/SFML-2.5.1/include -L/home/xnely/Downloads/SFML-2.5.1/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++

/** NOTE: This is a prototype. The design of the game has not yet been established. TODOs assume no change in design
 *  TODO: Handle game state. Allow for loading of different animations. Modularize code (all code is currently in game class).
 * */

#include <iostream>
#include "game.h"

int main(){
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