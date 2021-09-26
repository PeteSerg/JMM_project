/** 
 * Handles events called by main
 * */

#pragma once

#include "globals.h"

class Event{
public:
    void pollEvents();

    sf::Event ev;
};

inline void Event::pollEvents(){
    while(window->pollEvent(ev)){
        switch(ev.type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch(ev.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::Right:
                        rightPressed = true;
                        break;
                    case sf::Keyboard::Left:
                        leftPressed = true;
                        break;
                    case sf::Keyboard::Down:
                        downPressed = true;
                        break;
                    case sf::Keyboard::Up:
                        upPressed = true;
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch(ev.key.code){
                    case sf::Keyboard::Right:
                        rightPressed = false; break;
                    case sf::Keyboard::Left:
                        leftPressed = false; break;
                    case sf::Keyboard::Down:
                        downPressed = false; break;
                    case sf::Keyboard::Up:
                        upPressed = false; break;
                }
                break;
        }
    }
}

// void updateMousePositions(){
//     mousePosWindow = sf::Mouse::getPosition(*window);
//     mousePosView = window->mapPixelToCoords(mousePosWindow);
// }