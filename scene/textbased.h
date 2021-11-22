#pragma once

#include "scene.h"


#include <vector>
#include <iostream>
#include <fstream>

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
        " or an incorrectly implemented nextState pointer", 0, 1, {""}, {0, 0, 0, 0}};
        gameState initialState = {"Initial state", 0, 1, {""}, {0, 0, 0, 0}};
        gameState* current = &initialState;

        const uint32_t TIMEOUT = 500; // wait 500ms between clicks
        const sf::Vector2f rectFourthSize = sf::Vector2f(480.f, 270.f); // width of rect
        const sf::Vector2f rectThirdSize  = sf::Vector2f(640.f, 270.f);
        const sf::Vector2f rectHalfSize   = sf::Vector2f(960.f, 270.f);
        const sf::Vector2f rectWholeSize  = sf::Vector2f(1920.f, 270.f);
        const int rectHalfOffset = 960;
        const int rectThirdOffset = 640;
        const int rectFourthOffset = 480;

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

        inline void readStateTree(){ // State tree is forever loaded
            std::ifstream file;
            //file.open("tree/jmm-optional.tree");
            file.open(treeFileName);
            if(file.fail()){
                std::cout<<treeFileName<<" could not be opened.";
                file.close();
                file.open("tree/fail.tree");
                if(file.fail()){
                    std::cout<<"FAIL: tree files could not be loaded. Check your /tree directory\n";
                    file.close();
                    return;
                }
            }
            std::map<std::string, gameState*> map; // Refer to state by symbol "initial/next/etc"
            std::multimap<std::string, std::pair<int, gameState*>> wait; // If a nextState has not yet been defined
            std::string line;
            gameState *state;
            while(!file.eof()){
                state = new gameState;
                std::getline(file, line);
                if(!line.find("state")){// state is at 0
                    line = line.substr(6);
                    if(line.find("init") == 0) current = state; // init state
                    map.insert(std::pair<std::string, gameState*>(line, state)); // add symbol
                    std::multimap<std::string, std::pair<int, gameState*>>::iterator it;
                    while(wait.find(line) != wait.end()){
                        it = wait.find(line);
                        it->second.second->nextState[it->second.first] = state;
                        //wait.at(line).second->nextState[wait.at(line).first] = state;
                        wait.erase(it);
                    }
                }else{std::cout<<"state not found at 0 for line:"<<line<<'\n';return;}

                std::getline(file, line);
                line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                if(!line.find("prompt")){
                    line = line.substr(7);
                    state->prompt = line;
                }else{std::cout<<"prompt not found";return;}

                std::getline(file, line);
                line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                if(!line.find("sprite")){
                    line = line.substr(6);
                    state->sprite = std::stoi(line);
                }else{std::cout<<"sprite index not found";return;}

                std::getline(file, line);
                line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                if(!line.find("options")){
                    line = line.substr(7);
                    state->options = std::stoi(line);
                }else{std::cout<<"options index not found";return;}

                std::getline(file, line);
                line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                if(!line.find("optionPrompt{")){
                    std::getline(file, line);
                    line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                    int i = 0;
                    while(line != "}"){
                        state->optionPrompts[i] = line;
                        std::getline(file, line);
                        line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                        ++i;
                    }
                }else{std::cout<<"optionPrompt{ not found";return;}

                std::getline(file, line);
                line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                if(!line.find("nextState{")){
                    std::getline(file, line);
                    line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                    int i = 0;
                    while(line != "}"){
                        if(map.find(line) == map.end()) {
                            state->nextState[i] = nullptr;
                            wait.insert(std::pair<std::string, std::pair<int, gameState*>>(line, std::pair<int, gameState*>(i, state)));
                        }else state->nextState[i] = map.at(line);
                        std::getline(file, line); // }
                        line = line.substr(line.find_first_not_of(" \n\r\t\f\v"));
                        ++i;
                    }
                }else{std::cout<<"optionPrompt{ not found";return;}
            }
            file.close();
        }

        inline void reflectState(); // reflectState is used in init()

        inline void init(){
            readStateTree();
            // Sprite
            if(!texture.loadFromFile("textures/spritetest.png")){
                std::cout<<"Could not load sprite texture from file";
                //std::exit(0);
            }
            sprite.setTexture(texture);
            sprite.setScale(10,10);
            sprite.setPosition(710, 290);
            if(!ubuntuMono.loadFromFile("fonts/UbuntuMono-R.ttf")){
                std::cout<<"Could not load font from file";
                //std::exit(0);
            }
            prompt.setFont(ubuntuMono);
            prompt.setPosition(sf::Vector2f(0, 0));
            optionRect[0].setPosition(0,900);
            optionText[0].setPosition(0,900);
            optionText[0].setFont(ubuntuMono);
            optionText[1].setFont(ubuntuMono);
            optionText[2].setFont(ubuntuMono);
            optionText[3].setFont(ubuntuMono);
            optionRect[0].setFillColor(colors[0]);
            optionRect[1].setFillColor(colors[1]);
            optionRect[2].setFillColor(colors[2]);
            optionRect[3].setFillColor(colors[3]);
            reflectState();
        }

        inline void destroy(){
            // Only needed if you can reload the game
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

        const std::string escaped = "\\"; // NEW LINE SUPPORT
        inline std::string decode(std::string& input){
            std::string::size_type pos = 0;
            while((pos = input.find(escaped)) != std::string::npos){
               //input.replace(pos, 2, "\n");
               switch(input[pos+1]){
                   case 'n': input.replace(pos, 2, "\n"); break;
                   case '0': input.replace(pos, 2, ""); break;
               }
            }
            return input;
        }

        inline void reflectState(){ // Updates sfml objects to reflect those in current
            prompt.setString(decode(current->prompt)); 
            sprite.setTextureRect(sf::IntRect(current->sprite * 50, 0, current->sprite + 50, 50));
            // TODO: handle options
            options = current->options;
            switch (current->options){
            case 1:
                optionRect[0].setSize(rectWholeSize);
                optionText[0].setString(decode(current->optionPrompts[0]));
                break;
            case 2:
                optionRect[0].setSize(rectHalfSize);
                optionText[0].setString(decode(current->optionPrompts[0]));
                optionRect[1].setSize(rectHalfSize);
                optionRect[1].setPosition(rectHalfOffset, 900);
                optionText[1].setPosition(rectHalfOffset, 900);
                optionText[1].setString(decode(current->optionPrompts[1]));
                break;
            case 3:
                optionRect[0].setSize(rectThirdSize);
                optionText[0].setString(decode(current->optionPrompts[0]));
                optionRect[1].setSize(rectThirdSize);
                optionRect[1].setPosition(rectThirdOffset, 900);
                optionText[1].setPosition(rectThirdOffset, 900);
                optionText[1].setString(decode(current->optionPrompts[1]));
                optionRect[2].setSize(rectThirdSize);
                optionRect[2].setPosition(rectThirdOffset*2, 900);
                optionText[2].setPosition(rectThirdOffset*2, 900);
                optionText[2].setString(decode(current->optionPrompts[2]));
                break;
            case 4:
                optionRect[0].setSize(rectFourthSize);
                optionText[0].setString(decode(current->optionPrompts[0]));
                optionRect[1].setSize(rectFourthSize);
                optionRect[1].setPosition(rectFourthOffset, 900);
                optionText[1].setPosition(rectFourthOffset, 900);
                optionText[1].setString(decode(current->optionPrompts[1]));
                optionRect[2].setSize(rectFourthSize);
                optionRect[2].setPosition(rectFourthOffset*2, 900);
                optionText[2].setPosition(rectFourthOffset*2, 900);
                optionText[2].setString(decode(current->optionPrompts[2]));
                optionRect[3].setSize(rectFourthSize);
                optionRect[3].setPosition(rectFourthOffset*3, 900);
                optionText[3].setPosition(rectFourthOffset*3, 900);
                optionText[3].setString(decode(current->optionPrompts[3]));
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