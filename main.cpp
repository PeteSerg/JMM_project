// This does not need to be on the main branch, and can be deleted

//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

// x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/home/xnely/Downloads/SFML-2.5.1/include/
// x86_64-w64-mingw32-g++ -DSFML_STATIC -I/home/xnely/Downloads/SFML-2.5.1/include -L/home/xnely/Downloads/SFML-2.5.1/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++

/** PLAN: Implement grid with fixed number of frames of animation per movetick
 *        Use lack of talent to give really clean asthetic
 * */

#include <iostream>
#include "game.h"
#include "menu.h"

int main(){
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));
    // Init Game engine
    Game game;
    //Init Menu
    Menu menu(game.window.getSize().x, game.window.getSize().y);

    // Game loop
    while (game.running()){
        // Update
        game.update();
        // Render
        game.render();
    }

    sf::Window::pollEvent(sf::Event);
    menu.draw(game.window);
    while(window.pollEvent(sf::Event))
    {
        menu.runWhile();
    }

    return 0;
}