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

    // Game logic
    int points;
    int best;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    // Game Objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    sf::RenderWindow *window;
    sf::VideoMode videomode;
    sf::Event ev;
public:
    Game(/* args */);
    ~Game();

    const bool running() const;

    void spawnEnemy();
    void updateEnemies();
    void renderEnemies();

    void reset();

    void updateText();
    void renderText();

    void update();
    void render();

    void pollEvents();
    void updateMousePositions();
};