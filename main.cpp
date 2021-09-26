// This does not need to be on the main branch, and can be deleted

//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

// x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/home/xnely/Downloads/SFML-2.5.1/include/
// x86_64-w64-mingw32-g++ -DSFML_STATIC -I/home/xnely/Downloads/SFML-2.5.1/include -L/home/xnely/Downloads/SFML-2.5.1/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++

#include <iostream>
#include "game.h"
#include "event.h"
#include "window.h"

/** All data is public. Classes are only used for encapsulation of source code and provide no safety.
 *  One reason for this is to allow for easy refactoring of code.
 * Globals are declared here
 */
sf::RenderWindow *window;
sf::VideoMode videomode;
bool rightPressed, leftPressed, downPressed, upPressed = 0;

int main(){
    // Init window
    window = new sf::RenderWindow(videomode.getDesktopMode(), "Java minus minus", sf::Style::Fullscreen | sf::Style::Close);
    window->setFramerateLimit(145);
    // Init Game engine
    Game game;
    Event event;

    // Game loop
    while (window->isOpen()){
        // Update
        event.pollEvents();
        game.update();
        // Render
        game.render();
    }

    return 0;
}