/** Game engine
 *  Wrapper class
 * */
#pragma once

#include "globals.h"

class Game
{
private:

    void initVariables();
    void initScene();

    // Clock
    sf::Clock deltaClock; // Used for calculating __ over time ratios
    sf::Clock clock; // Does not reset. Overflow used for cyclical animation

public:
    Game(/* args */);
    ~Game();

    void tick();

    // Test data
    void renderTestSprite();

    void update();
    void render();
};