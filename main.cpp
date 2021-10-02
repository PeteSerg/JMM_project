// This does not need to be on the main branch, and can be deleted

//g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

// x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/home/xnely/Downloads/SFML-2.5.1/include/
// x86_64-w64-mingw32-g++ -DSFML_STATIC -I/home/xnely/Downloads/SFML-2.5.1/include -L/home/xnely/Downloads/SFML-2.5.1/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++

#include <iostream>
#include "game.h"
#include "event.h"
#include "globals.h"

/** Globals are used to allow easy refactoring of code.
 * Globals are declared here
 */
Scene currentScene = Scene::Default;
sf::RenderWindow *window;
sf::VideoMode videomode;
uint32_t millis;
float delta;
bool rightPressed, leftPressed, downPressed, upPressed = 0;
bool leftClick = 0;
sf::Vector2i mousePosWindow;
sf::Vector2f mousePosView;

int main(){
    // Init window
    window = new sf::RenderWindow(videomode.getDesktopMode(), "Java minus minus", sf::Style::Fullscreen | sf::Style::Close);
    window->setFramerateLimit(145);
    // Init Game engine
    Game game;
    Event event;

    // Game loop
    while (window->isOpen()){
        event.update();
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}