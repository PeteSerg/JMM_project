// g++ -c main.cpp scene.cpp && g++ main.o scene.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
// First attempt at making something actually worth something

#include "scene.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main(){
    sf::RenderWindow window(sf::VideoMode(400, 400), "Art");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)// "close requested" event: we close the window
                window.close();
        }
        window.clear(sf::Color::Black); //CLEAR
        //DRAW
        Scene circleScene("sample.scene", &window);
        circleScene.draw();
        window.display(); //DISPLAY
    }

    return 0;
}