/** Game engine
 *  Wrapper class
 * */
#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu {
    public:
        Menu(float width, float height);
        ~Menu();

        void draw(sf::RenderWindow &window);
        void moveUp();
        void moveDown();
        int getPressedItem() {return selectedItemIndex;}
        void runWhile();

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::RenderWindow *window;
};