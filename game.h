/** Game engine
 *  Wrapper class
 * */
#pragma once

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

    // Clock
    sf::Clock deltaClock; // Used for calculating __ over time ratios
    sf::Clock clock; // Does not reset. Overflow used for cyclical animation

    // Testing data
    sf::RectangleShape box;
    sf::Vector2f boxPos;
    bool boxDirection;
    sf::Texture testTexture;
    sf::RectangleShape testRect;
    sf::Sprite testSprite;

public:
    Game(/* args */);
    ~Game();

    void tick();

    // Test data
    void renderBox();
    void updateBox();
    void renderTestSprite();

    void update();
    void render();

    enum Scene {Default};
    Scene scene;

    uint32_t millis;
    float delta; // Milliseconds elapsed while rendering. Assumes that rendering takes a majority of time.
};