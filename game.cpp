#include "game.h"
#include "window.h"
#include "event.h"
// Private Functions
void Game::initVariables(){
    delta = millis = 0;
    scene = Default;

    // Test sprite and object (box)
    box.setSize(sf::Vector2f(50.f,50.f));
    boxPos = sf::Vector2f(0.f,0.f);
    boxDirection = false;
    if(!testTexture.loadFromFile("textures/spritetest.png")){
        std::cout<<"Could not load sprite texture from file";
        std::exit(0);
    }
    testSprite.setTexture(testTexture);
    testSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    testSprite.setScale(10,10);//290, 710
    testSprite.setPosition(710, 290);
}

// CONSTRUCTORS
Game::Game() {
    initVariables();
}

Game::~Game(){

}

void Game::tick(){
    millis = clock.getElapsedTime().asMilliseconds();
}

// Test box
void Game::renderBox(){
    box.setPosition(boxPos.x,boxPos.y);
    window->draw(box);
}
void Game::updateBox(){
    if(boxDirection)
        if(boxPos.x - 1880 * delta <= 0){ // 1880px/s
            boxPos.x = 0; boxDirection = 0;
        }
        else boxPos.x -= 1880 * delta;
    else
        if(boxPos.x + 1880 * delta >= 1880){
            boxPos.x = 1880; boxDirection = 1;
        }
        else boxPos.x += 1880 * delta;
}

void Game::renderTestSprite(){
    testSprite.setTextureRect(sf::IntRect(0, ((millis>>7)&7)*50, 50, 50)); // 8 states / 1.024 seconds
    window->draw(testSprite);
}

void Game::update() {
    tick();

    // Test box
    updateBox();
}

void Game::render() {
    deltaClock.restart(); // Begin deltaTimer
    // Clear
    window->clear();

    // Render
    switch(scene){
        case Default:
            break;
    }
    // Test objects
    renderBox();
    renderTestSprite();

    // Display
    window->display();

    // Calculate time
    delta = deltaClock.getElapsedTime().asSeconds();
}

// void Game::updateMousePositions(){
//     mousePosWindow = sf::Mouse::getPosition(*window);
//     mousePosView = window->mapPixelToCoords(mousePosWindow);
// }