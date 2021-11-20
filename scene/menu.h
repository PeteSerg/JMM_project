#pragma once

#include "scene.h"

#include <vector>
#include <iostream>

/** Note that only headers are used to make
 *  adding new scenes easy
 * */
namespace scene{
    namespace menu{
        std::vector<sf::RectangleShape> rects;
        std::vector<sf::Sprite> sprites;
        /** DEBUG: temp indicate purpose of menu*/
        sf::Font ubuntuMono;
        sf::Text warn, begin, quit;
        sf::Texture texture; // USED in sprite test
        /** END: DEBUG*/

        /** Initialize sets all initial variables for the scene
         *  and loads any scene-specific files/textures
         * */
        inline void init(){ /** TODO: Implement */
            // initialize simple grey rectangle
            sf::RectangleShape rect, bruh;
            rect.setPosition(610.f, 290.f);
            rect.setSize(sf::Vector2f(250.f, 250.f));
            rect.setFillColor(sf::Color(64, 64, 128, 255));
            rects.push_back(rect);
            bruh.setPosition(1110.f, 290.f);
            bruh.setSize(sf::Vector2f(250.f, 250.f));
            bruh.setFillColor(sf::Color(64, 64, 128, 255));
            rects.push_back(bruh);
            // indicate purpose of menu
            if(!ubuntuMono.loadFromFile("fonts/UbuntuMono-R.ttf")){
                std::cout<<"Could not load font from file";
                std::exit(0);
            }
            warn.setString("       The Wall");
            warn.setFont(ubuntuMono);
            warn.setPosition(sf::Vector2f(810.f, 150.f));
            begin.setString("Start");
            begin.setFont(ubuntuMono);
            begin.setPosition(sf::Vector2f(680.f, 390.f));
            quit.setString("Commit");
            quit.setFont(ubuntuMono);
            quit.setPosition(sf::Vector2f(1180.f, 390.f));
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
            window->draw(begin);
            window->draw(quit);
        }
        /** Any game logic branches off from here **/
        inline void update(){ /** TODO: Implement */
            // Destroy current scene and initialize next
            // Switch to different scene based on menu selection
            if(leftClick){ // Find mouse position on leftClick
            //1110.f, 290.f
                if(mousePosWindow.x >= 610.f && mousePosWindow.x <= 860){
                    if(mousePosWindow.y >= 290.f && mousePosWindow.y <= 540){
                        destroy();
                        scene::textbased::init();
                        currentScene = Scene::TextBased;
                    }
                }
                else if(mousePosWindow.x >= 1110.f && mousePosWindow.x <= 1360){
                    if(mousePosWindow.y >= 290.f && mousePosWindow.y <= 540){
                        exit(0);
                    }
                }
            }
        }
    };
}