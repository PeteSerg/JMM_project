#pragma once

#include "scene.h"

#include <vector>
#include <iostream>

/** There is no logical reason to use a class here
 *  This file is simply used to physically seporate
 *  scene-specific code from game.cpp
 * */
namespace scene{
    namespace lvl1{
        std::vector<sf::RectangleShape> rects;
        std::vector<sf::Sprite> sprites;
        sf::Texture texture;

        // Game system variables
        sf::Vector2f eggyPos(160.f, 140.f);
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
            // Updates position of eggy. Copied code. We probably want eggy to move 50px at a time
            if(leftPressed && eggyPos.x - 500 * delta <= 160) eggyPos.x = 160;
            else if(leftPressed) eggyPos.x -= 500 * delta;
            else if(rightPressed && eggyPos.x + 500 * delta >= 1710) eggyPos.x = 1710;
            else if(rightPressed) eggyPos.x += 500 * delta;
            else if(upPressed && eggyPos.y - 500 * delta <= 140) eggyPos.y = 140;
            else if(upPressed) eggyPos.y -= 500 * delta;
            else if(downPressed && eggyPos.y + 500 * delta >= 890) eggyPos.y = 890;
            else if(downPressed) eggyPos.y += 500 * delta;
            else return;

            sprites[eggyID].setPosition(eggyPos.x,eggyPos.y); // Update position of eggy's sprite
            // Eggy has sprite 'id' = 0.
        }
    };
}