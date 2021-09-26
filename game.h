/** Game engine
 *  Wrapper class
 * */
#pragma once

#include "scene/default.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    void initVariables();
    void initScene();

    // Clock
    sf::Clock deltaClock; // Used for calculating __ over time ratios
    sf::Clock clock; // Does not reset. Overflow used for cyclical animation

    // Scenes
    scene::Default defaultScene;

    // Testing data
    sf::Texture testTexture;
    sf::Sprite testSprite;

public:
    Game(/* args */);
    ~Game();

    void tick();

    // Test data
    void renderTestSprite();

    void update();
    void render();

    enum Scene {Default};
    Scene scene;
};