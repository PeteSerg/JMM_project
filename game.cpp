#include "game.h"
#include "scene/scene.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

// Private Functions
void Game::initVariables(){
    delta = millis = 0;
    currentScene = Scene::Default;
    /** DEBUG: load menu currentScene*/
    currentScene = Scene::TextBased;
    scene::textbased::init();
    /** END: Debug */
}
// The default scene is always initialized
void Game::initScene(){
    scene::Default::init();
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
    switch(currentScene){
        case Scene::Default:
            scene::Default::update();
            break;
        case Scene::Menu:
            scene::menu::update();
            break;
        case Scene::TextBased:
            scene::textbased::update();
            break;
        case Scene::Lvl:
            scene::lvl::update();
            break;
    }
}

void Game::render() {
    deltaClock.restart(); // Begin deltaTimer

    window->clear();

    // Render
    switch(currentScene){
        case Scene::Default:
            scene::Default::render();
            break;
        case Scene::Menu:
            scene::menu::render();
            break;
        case Scene::TextBased:
            scene::textbased::render();
            break;
        case Scene::Lvl:
            scene::lvl::render();
            break;
    }

    window->display();

    // Calculate deltaTime
    delta = deltaClock.getElapsedTime().asSeconds();
}