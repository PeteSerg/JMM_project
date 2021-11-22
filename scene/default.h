#pragma once
#include "scene.h"

#include <iostream>

/** Other scenes can be made based of of this default scene.
 *  This class demonstrates initializing, updating, and rendering sprites and text.
 * */
namespace scene{
    namespace Default{
        // Declarations
        /** Avoid many explicit declarations.
         *  Try to use things like vectors that are only
         *  populated on initialization (as seen in scene/menu.h)
         */
        void updateBox();
        void renderSprite();
        // Moving rect using delta
        sf::RectangleShape box;
        sf::Vector2f boxPos;
        // Animated sprite using millis
        sf::Texture texture;
        sf::Sprite sprite;
        // Warning text
        sf::Font ubuntuMono;
        sf::Text warn;

        // Functions
        /** Initialize sets all initial variables for the scene
         *  and loads any scene-specific files/textures
         * */
        inline void init(){
            // Rectangle
            box.setSize(sf::Vector2f(50.f,50.f));
            box.setFillColor(sf::Color::Magenta);
            boxPos = sf::Vector2f(0.f,0.f);
            // Sprite
            if(!texture.loadFromFile("textures/spritetest.png")){
                std::cout<<"Could not load sprite texture from file";
                std::exit(0);
            }
            sprite.setTexture(texture); // The texture is 50px wide and 400px tall
            sprite.setTextureRect(sf::IntRect(0, 0, 50, 50)); // Selects a 50px x 50px area of the texture to draw
            sprite.setScale(10,10); // Each texture pixel now represents 10 on the screen
            sprite.setPosition(710, 290);
            // Text Warning
            if(!ubuntuMono.loadFromFile("fonts/UbuntuMono-R.ttf")){
                std::cout<<"Could not load font from file";
                std::exit(0);
            }
            warn.setString("This is the default scene. This should not be seen by the end user.");
            warn.setFont(ubuntuMono);
            warn.setPosition(sf::Vector2f(500, 930));
        }

        /** Deletes all dynamically allocated memory
         *  Should be called if the scene is no longer
         *  needed or needs to be reset
         * 
         *  The default scene does not use destroy because
         *  it has no dynamic memory and is always loaded
         * */
        inline void destroy(){
        }

        /** Self explanatory. Draw to the window
         *  Sprite animations can be handled here
         * */
        inline void render(){
            renderSprite();
            window->draw(box);
            window->draw(warn);
        }
        /** Any game logic branches off from here **/
        inline void update(){
            updateBox();
        }

        /** In this example, the only game logic has
         *  to do with player movement.
         *  We can use the current state of the arrow keys
         *  to determine how the box should move.
         * 
         *  A real implementation would use vars like leftReleased
         *  (implemented in event.h) to give precedence to the first
         *  key to be pressed and held
         * */
        inline void updateBox(){
            if(leftPressed && boxPos.x - 500 * delta <= 0) boxPos.x = 0;             // Collide with left edge of screen
            else if(leftPressed) boxPos.x -= 500 * delta;                            // Move left 
            else if(rightPressed && boxPos.x + 500 * delta >= 1870) boxPos.x = 1870; // Collide with right edge of screen
            else if(rightPressed) boxPos.x += 500 * delta;                           // Move right
            else if(upPressed && boxPos.y - 500 * delta <= 0) boxPos.y = 0;          // Collide with top of screen
            else if(upPressed) boxPos.y -= 500 * delta;                              // Move up 
            else if(downPressed && boxPos.y + 500 * delta >= 1030) boxPos.y = 1030;  // Collide with bottom of screen
            else if(downPressed) boxPos.y += 500 * delta;                            // Move down
            else return;                        // Don't update position if not needed

            box.setPosition(boxPos.x,boxPos.y); // Update position of box
        }

        /** In this example, we wan't to render an animation at ~8 fps.
         *  To do this, we take 1000 milliseconds / 128 = 7.8125 fps
         *                   or 1024 milliseconds / 128 = 8.0000
         *  If we want more percision, we can use actual divides.
         *  To reset back to frame 0 after frame 7, mod the result by 8
         * 
         *  This can be modified to get any framerate desired.
         * */
        inline void renderSprite(){
        //                     bitshift 7 = divide by 128⬎   ⬐ bitwise & 7 = mod by 8
            sprite.setTextureRect(sf::IntRect(0, ((millis>>7)&7)*50, 50, 50));     // 8 states / 1.024 seconds
        // lastly multiply by 50 to shift 50 pixels down texture⬏
            window->draw(sprite);
        }
    };
}