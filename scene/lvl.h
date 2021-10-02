#pragma once

#include "scene.h"

#include <vector>
#include <iostream>

/** There is no logical reason to use a class here
 *  This file is simply used to physically seporate
 *  scene-specific code from game.cpp
 * */
namespace scene{
    namespace lvl{
        // Dynamically allocated memory
        // Empty until used - freed when done
        std::vector<sf::RectangleShape> rects;
        std::vector<sf::Sprite> sprites;
        sf::Texture texture; // Texture must live as long as sprites

        // Statically allocated variables
        // Since these are basically global variables that never really
        // go out of scope. They should be used sparingly if possible.
        //
        // We may need to refactor the switch statements in game so that
        // our scenes are only in scope when we are using them, but we can
        // still easily switch between them while still using update+render+timers
        sf::Vector2f eggyPos(160.f, 140.f);
        uint32_t moveTimeOut = 0;
        enum direction {right, left, down, up};
        direction eggyDir = left;
        // This should maybe be replaced with an entity component system
        size_t eggyID;

        inline void init(){
            sf::RectangleShape rect;
            rect.setPosition(160.f, 140.f);
            rect.setSize(sf::Vector2f(1600.f, 800.f));
            rect.setFillColor(sf::Color(22, 23, 18, 255));
            rects.push_back(rect); // background
            rect.setPosition(1710.f, 890.f);
            rect.setSize(sf::Vector2f(50.f, 50.f));
            rect.setFillColor(sf::Color(255, 0, 0, 255));
            rects.push_back(rect); // bottom right
            if(!texture.loadFromFile("textures/eggy.png")){
                std::cout<<"Could not load sprite texture from file";
                std::exit(0);
            }
            sf::Sprite sprite;
            sprite.setTexture(texture); 
            sprite.setTextureRect(sf::IntRect(0, 0, 50, 50)); 
            sprite.setPosition(160.f, 140.f);
            sprites.push_back(sprite);
            eggyID = sprites.size() - 1;
        }

        inline void destroy(){
            texture.create(1, 1); // I think this has the effect of unloading eggy.png
            rects.clear();
            sprites.clear();
        }

        inline void render(){
            for(size_t i=0; i<rects.size(); ++i){
                window->draw(rects[i]);
            }
            // If all sprites can be kept contiguous in memory,
            // This will scale very efficiently to thousands of sprites.
            for(size_t i=0; i<sprites.size(); ++i){
                window->draw(sprites[i]);
            }
        }
        
        inline void update(){
            if(millis>moveTimeOut){
                if(leftPressed && eggyPos.x - 50 < 160 || leftPressed && rightPressed) return;
                else if(leftPressed) {eggyPos.x -= 50; eggyDir = left;}
                else if(rightPressed && eggyPos.x + 50 > 1710) return;
                else if(rightPressed) {eggyPos.x += 50; eggyDir = right;}
                else if(upPressed && eggyPos.y - 50 < 140 || upPressed && downPressed) return;
                else if(upPressed) {eggyPos.y -= 50; eggyDir = down;}
                else if(downPressed && eggyPos.y + 50 > 890) return;
                else if(downPressed) {eggyPos.y += 50; eggyDir = up;}
                else return;
                moveTimeOut = millis + 200;
            }else{
                int interpolate = (moveTimeOut-millis)/5; // divisor of 4 is maximally smooth
                switch(eggyDir){
                    case left:
                        sprites[eggyID].setPosition(eggyPos.x + interpolate,eggyPos.y );
                        break;
                    case right:
                        sprites[eggyID].setPosition(eggyPos.x - interpolate,eggyPos.y );
                        break;
                    case down:
                        sprites[eggyID].setPosition(eggyPos.x,eggyPos.y + interpolate);
                        break;
                    case up:
                        sprites[eggyID].setPosition(eggyPos.x,eggyPos.y - interpolate);
                }
                return;
            }

        }
    };
}