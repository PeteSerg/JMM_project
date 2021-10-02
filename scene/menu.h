#pragma once

#include "../globals.h"

#include <vector>

/** There is no logical reason to use a class here
 *  This file is simply used to physically seporate
 *  scene-specific code from game.cpp
 * */
namespace scene{
    namespace menu{
        std::vector<sf::RectangleShape> rects;
        std::vector<sf::Sprite> sprites;
        /** DEBUG: temp indicate purpose of menu*/
        sf::Font ubuntuMono;
        sf::Text warn;
        /** END: DEBUG*/

        /** Initialize sets all initial variables for the scene
         *  and loads any scene-specific files/textures
         * */
        inline void init(){ /** TODO: Implement */
            // initialize simple grey rectangle
            sf::RectangleShape rect;
            rect.setPosition(710.f, 290.f);
            rect.setSize(sf::Vector2f(500.f, 500.f));
            rect.setFillColor(sf::Color(128, 126, 128, 255));
            rects.push_back(rect);
            // indicate purpose of menu
            if(!ubuntuMono.loadFromFile("fonts/UbuntuMono-R.ttf")){
                std::cout<<"Could not load font from file";
                std::exit(0);
            }
            warn.setString("This is the menu scene (unimplemented). Click the box to switch to the default scene.");
            warn.setFont(ubuntuMono);
            warn.setPosition(sf::Vector2f(400, 930));
        }
        /** Deletes all dynamically allocated memory
         *  Should be called if the scene is no longer
         *  needed or needs to be reset
         * */
        inline void destroy(){
            rects.clear();
            sprites.clear();
        }

        /** Self explanatory. Draw to the window
         *  Sprite animations can be handled here
         * */
        inline void render(){
            /** DEBUG: render explaination text */
            window->draw(warn);
            /** END: debug */
            for(size_t i=0; i<rects.size(); ++i){
                window->draw(rects[i]);
            }
            for(size_t i=0; i<sprites.size(); ++i){
                window->draw(sprites[i]);
            }
        }
        /** Any game logic branches off from here **/
        inline void update(){ /** TODO: Implement */
            // Switch to different scene based on menu selection
            // Scene does not need to be initialized bc default is always initialized
            if(leftClick){ // Find mouse position on leftClick
                if(mousePosWindow.x >= 710.f && mousePosWindow.x <= 1210){
                    if(mousePosWindow.y >= 290.f && mousePosWindow.y <= 790){
                        destroy();
                        currentScene = Scene::Default;
                    }
                }
            }
        }
    };
}