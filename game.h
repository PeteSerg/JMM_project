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
    void initWindow();
    void initEnemies();
    void initFonts();
    void initText();

    // Resources
    sf::Font font;

    // Text
    sf::Text inputText;
    sf::Text outputText;

    // Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Pressed keys
    bool rightPressed, leftPressed, downPressed, upPressed;

    // Clock
    /** TODO: Timer thread is not needed. Game should use time elapsed
     *        since last update to determine tick and use delta for motion.
     * */
    //sf::Thread clock;
    sf::Clock deltaClock; // Used for calculating __ over time ratios
    sf::Clock clock; // Does not reset, only overflow
    uint32_t millis;
    float delta; // Milliseconds elapsed while rendering. Assumes that rendering takes a majority of time.
    // With wait = 4, tock overflows every second + 24 millis
    // int wait; // Higher wait = lower tick speed

    // Game logic
    std::string input;
    std::string output;

    // Game Objects
    sf::RectangleShape box;
    sf::Vector2f boxPos;
    bool boxDirection; // false = right
    sf::Texture testTexture;
    sf::RectangleShape testRect;
    sf::Sprite testSprite;

    sf::RenderWindow *window;
    sf::VideoMode videomode;
    sf::Event ev;
public:
    Game(/* args */);
    ~Game();

    const bool running() const;

    void tick();

    void updateText();
    void renderText();

    // Game Objects

    // Game Logic
    void execute(std::string command);

    void renderBox();
    void updateBox();
    void renderTestSprite();

    void update();
    void render();

    void pollEvents();
    void updateMousePositions();
};