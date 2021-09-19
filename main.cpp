// This does not need to be on the main branch, and can be deleted

//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

// Compile for windows:
// x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/home/xnely/Downloads/SFML-2.5.1/include/
// x86_64-w64-mingw32-g++ -DSFML_STATIC -I/home/xnely/Downloads/SFML-2.5.1/include -L/home/xnely/Downloads/SFML-2.5.1/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++

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