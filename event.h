/** 
 * Handles events called by main
 * */

#pragma once

#include "globals.h"

class Event{
public:
    void update();
private:
    sf::Event ev;
};

inline void Event::update(){
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
            case sf::Event::MouseButtonPressed:
                switch(ev.mouseButton.button){
                    case sf::Mouse::Button::Left:
                        leftClick = true; break;
                }
                break;
            case sf::Event::MouseButtonReleased:
                switch(ev.mouseButton.button){
                    case sf::Mouse::Button::Left:
                        leftClick = false; break;
                }
                break;
        }
    }
    // Update mouse position
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}