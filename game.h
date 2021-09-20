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
    sf::Text currentText;
    sf::Text bestText;

    // Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Pressed keys
    bool rightPressed, leftPressed, downPressed, upPressed;

    // Clock
    sf::Thread clock;
    sf::Clock timer;
    bool exit; // used to kill timer thread
    // With wait = 4, tock overflows every second + 24 millis
    int wait; // Higher wait = lower tick speed
    unsigned char tock;

    // Game logic
    std::string input;

    // Game Objects
    sf::RectangleShape box;
    sf::Vector2f boxPos;
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
    void renderTestSprite();

    void update();
    void render();

    void pollEvents();
    void updateMousePositions();
};