#pragma once

#include "scene.h"


#include <vector>
#include <iostream>

namespace scene{
    namespace textbased{
        struct gameState{
            std::string prompt;             // Prompt for the current state
            uint32_t sprite;                // X position of sprite on sprite sheet
            int options;                    // # of options
            std::string optionPrompts[4];   // Prompts for options
            gameState* nextState[4];        // State to jump to on option picked
        };

        gameState badState = {"A bad game state has been reached.\nThis may be caused by the choice of an unimplemented option"
        " or an incorrectly implemented nextState pointer", 0, 0, {""}, {0, 0, 0, 0}};
        gameState initialState = {"Initial state", 0, 1, {""}, {0, 0, 0, 0}};
        gameState* current = &initialState;

        const uint32_t TIMEOUT = 500; // wait 500ms between clicks
        const sf::Vector2f rectFourthSize = sf::Vector2f(480.f, 270.f); // width of rect
        const sf::Vector2f rectThirdSize  = sf::Vector2f(640.f, 270.f);
        const sf::Vector2f rectHalfSize   = sf::Vector2f(960.f, 270.f);
        const sf::Vector2f rectWholeSize  = sf::Vector2f(1920.f, 270.f);

        sf::Texture texture;
        sf::Sprite sprite;
        sf::Font ubuntuMono;
        sf::Text prompt; // Max width 124 characters before return
        sf::Color colors[] = {sf::Color(255,0,0,255), sf::Color(0,255,0,255), sf::Color(0,0,255,255), sf::Color(0,255,255,255)};
        sf::RectangleShape optionRect[] = {sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape()};
        sf::Text optionText[] = {sf::Text(), sf::Text(), sf::Text(), sf::Text()}; // Max width 32 characters before return for 4 choices
        int maxOptionWidth = 1920;

        int promtLength = 0;
        std::string promptString = "";

        uint32_t timeOut = 0; // WARN: no overflow guard
        int options = 4;

        inline void init(){
            // Sprite
            if(!texture.loadFromFile("textures/spritetest.png")){
                std::cout<<"Could not load sprite texture from file";
                //std::exit(0);
            }
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, 50, 50)); // Selects a 50px x 50px area of the texture to draw
            sprite.setScale(10,10);
            sprite.setPosition(710, 290);
            if(!ubuntuMono.loadFromFile("fonts/UbuntuMono-R.ttf")){
                std::cout<<"Could not load font from file";
                //std::exit(0);
            }
            prompt.setFont(ubuntuMono);
            prompt.setString("INITIALIZED");
            prompt.setPosition(sf::Vector2f(0, 0));
            optionText[0].setFont(ubuntuMono);
            optionText[0].setString("INITIALIZED");
            optionText[0].setPosition(0, 900);
            optionText[1].setFont(ubuntuMono);
            optionText[1].setString("INITIALIZED");
            optionText[1].setPosition(480, 900);
            optionText[2].setFont(ubuntuMono);
            optionText[2].setString("INITIALIZED");
            optionText[2].setPosition(960, 900);
            optionText[3].setFont(ubuntuMono);
            optionText[3].setString("INITIALIZED");
            optionText[3].setPosition(1440, 900);
            // Init option rects
            optionRect[0].setPosition(0,900);
            optionRect[0].setSize(rectFourthSize);
            optionRect[0].setFillColor(colors[0]);
            optionRect[1].setPosition(480,900);
            optionRect[1].setSize(rectFourthSize);
            optionRect[1].setFillColor(colors[1]);
            optionRect[2].setPosition(960,900);
            optionRect[2].setSize(rectFourthSize);
            optionRect[2].setFillColor(colors[2]);
            optionRect[3].setPosition(1440,900);
            optionRect[3].setSize(rectFourthSize);
            optionRect[3].setFillColor(colors[3]);
        }

        inline void destroy(){

        }

        inline void render(){
            window->draw(prompt);
            window->draw(sprite);
            if(options)
            for(int i=0;i<options;++i){
                window->draw(optionRect[i]);
                window->draw(optionText[i]);
            }
            else{
                window->draw(optionRect[0]);
                window->draw(optionText[0]);
            }
        }

        inline void reflectState(){ // Updates sfml objects to reflect those in current
            prompt.setString(current->prompt); 
            sprite.setTextureRect(sf::IntRect(current->sprite, 0, current->sprite + 50, 50));
            // TODO: handle options
            options = current->options;
            switch (current->options){
            case 1:
                optionRect[0].setSize(rectWholeSize);
                optionText[0].setString(current->optionPrompts[0]);
                break;
            case 2:
                optionRect[0].setSize(rectHalfSize);
                optionText[0].setString(current->optionPrompts[0]);
                optionRect[1].setSize(rectHalfSize);
                optionText[1].setString(current->optionPrompts[1]);
                break;
            case 3:
                optionRect[0].setSize(rectThirdSize);
                optionText[0].setString(current->optionPrompts[0]);
                optionRect[1].setSize(rectThirdSize);
                optionText[1].setString(current->optionPrompts[1]);
                optionRect[2].setSize(rectThirdSize);
                optionText[2].setString(current->optionPrompts[2]);
                break;
            case 4:
                optionRect[0].setSize(rectFourthSize);
                optionText[0].setString(current->optionPrompts[0]);
                optionRect[1].setSize(rectFourthSize);
                optionText[1].setString(current->optionPrompts[1]);
                optionRect[2].setSize(rectFourthSize);
                optionText[2].setString(current->optionPrompts[2]);
                optionRect[3].setSize(rectFourthSize);
                optionText[3].setString(current->optionPrompts[3]);
                break;
            default:
                options = 0; // invalid -> set to zero to prevent fault
                optionRect[0].setSize(rectWholeSize);
                optionText[0].setString("The current game state has an invalid number of options: "+std::to_string(current->options));
            }
        }
        
        inline void update(){
            if(leftClick && timeOut < millis && mousePosWindow.y >= 900 && mousePosWindow.x <= 1920){
                //prompt.setString(std::to_string(mousePosWindow.y));
                //prompt.setString(std::to_string(millis));
                //prompt.setString(std::to_string(options * mousePosWindow.x / 1920));
                if(current) current = current->nextState[options * mousePosWindow.x / 1920];
                else current = &badState;
                if(current) reflectState();
                timeOut = millis + TIMEOUT;
            }
        }
    };
}