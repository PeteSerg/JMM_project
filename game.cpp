#include "game.h"
#include "globals.h"
#include "event.h"
// Private Functions
void Game::initVariables(){
    delta = millis = 0;
    scene = Default;

    // Test sprite
    if(!testTexture.loadFromFile("textures/spritetest.png")){
        std::cout<<"Could not load sprite texture from file";
        std::exit(0);
    }
    testSprite.setTexture(testTexture);
    testSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    testSprite.setScale(10,10);//290, 710
    testSprite.setPosition(710, 290);
}
void Game::initScene(){
    defaultScene.init();
}

// CONSTRUCTORS
Game::Game() {
    initVariables();
    initScene();
}

Game::~Game(){

}

void Game::tick(){
    millis = clock.getElapsedTime().asMilliseconds();
}

void Game::renderTestSprite(){
    testSprite.setTextureRect(sf::IntRect(0, ((millis>>7)&7)*50, 50, 50)); // 8 states / 1.024 seconds
    window->draw(testSprite);
}

void Game::update() {
    tick();

    // Update
    switch(scene){
        case Default:
            defaultScene.update();
            break;
    }
}

void Game::render() {
    deltaClock.restart(); // Begin deltaTimer
    // Clear
    window->clear();

    // Render
    switch(scene){
        case Default:
            defaultScene.render();
            break;
    }
    // Test Sprite
    renderTestSprite();

    // Display
    window->display();

    // Calculate time
    delta = deltaClock.getElapsedTime().asSeconds();
}