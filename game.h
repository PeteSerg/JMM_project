/** Game engine
 *  Wrapper class
 * */
#pragma once

#include <iostream>
#include <vector>
#include <ctime>

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
    int tickTime; // How many milliseconds thread will wait between ticks
    bool hasMovedThisTick; // Stores if player has moved since last time out
    int moveTimeOut; // Prevent player from moving too quickly

    // Game logic
    sf::Vector2f playerPos;

    // Game Objects
    sf::RectangleShape player;
    sf::Vector2f playerLast;

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
    void updatePlayer();
    void renderPlayer();

    void update();
    void render();

    void pollEvents();
    void updateMousePositions();
};