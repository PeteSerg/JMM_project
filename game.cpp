#include "game.h"
#include "globals.h"
#include "event.h"
// Private Functions
void Game::initVariables(){
    delta = millis = 0;
    scene = Default;
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

    window->clear();

    // Render
    switch(scene){
        case Default:
            defaultScene.render();
            break;
    }

    window->display();

    // Calculate deltaTime
    delta = deltaClock.getElapsedTime().asSeconds();
}