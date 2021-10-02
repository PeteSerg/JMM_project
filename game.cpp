#include "game.h"
#include "scene/scene.h"
// Private Functions
void Game::initVariables(){
    delta = millis = 0;
    currentScene = Scene::Default;
    /** DEBUG: load menu currentScene*/
    currentScene = Scene::Menu;
    scene::menu::init();
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
        case Scene::Lvl1:
            scene::lvl1::update();
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
        case Scene::Lvl1:
            scene::lvl1::render();
            break;
    }

    window->display();

    // Calculate deltaTime
    delta = deltaClock.getElapsedTime().asSeconds();
}