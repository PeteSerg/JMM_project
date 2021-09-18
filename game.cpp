#include "game.h"
// Private Functions
void Game::initVariables(){
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->best = 0;
    this->enemySpawnTimerMax = 36.f;
    this->enemySpawnTimer = enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}
void Game::initEnemies(){
    this->enemy.setPosition(sf::Vector2f(375.f, 275.f));
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
}
void Game::initWindow(){
    this->videomode.height = 1080;//600;
    this->videomode.width = 1920;//800;
    this->window = new sf::RenderWindow(this->videomode, "Java minus minus", sf::Style::Fullscreen | sf::Style::Close);

    this->window->setFramerateLimit(144);
}
void Game::initFonts(){
    if(!this->font.loadFromFile("LiberationMono-Bold.ttf"))std::cerr<<"ERROR::GAME::INITFONTS::Failed to load font LiberationMono-Bold.tff\n";
}
void Game::initText(){
    this->currentText.setFont(font);
    this->currentText.setCharacterSize(32);
    this->currentText.setFillColor(sf::Color::White);

    this->bestText.setFont(font);
    this->bestText.setCharacterSize(32);
    this->bestText.setFillColor(sf::Color::White);
    this->bestText.setPosition(sf::Vector2f(1750.f, 0.f));
}

// CONSTRUCTORS
Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initEnemies();
    this->initFonts();
    this->initText();
}

Game::~Game(){
    delete this->window;
}

// ACCESSORS
const bool Game::running() const{
    return this->window->isOpen();
}

void Game::pollEvents(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::R:
                        reset();
                }
                break;
        }
    }
}

void Game::reset(){
    enemies.clear();
}

// PUBLIC
// UPDATE
void Game::update() {
    pollEvents();
    updateMousePositions();

    updateEnemies();
    updateText();
}

void Game::render() {
    // Clear
    window->clear();

    // Render
    renderEnemies();

    // UI
    renderText();

    // Display
    window->display();
}

void Game::updateMousePositions(){
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::spawnEnemy(){
    enemy.setPosition(
        static_cast<float>(rand()%static_cast<int>(window->getSize().x - enemy.getSize().x)),
        0.f
    );

    enemy.setFillColor(sf::Color::Green);
    enemies.push_back(enemy);
}
void Game::updateEnemies(){
    if(enemies.size()<maxEnemies)
    if(enemySpawnTimer >= enemySpawnTimerMax) { // Spawn enemy and reset timer
        spawnEnemy();
        enemySpawnTimer = 0.f;
    }
    else enemySpawnTimer += 1.f;

    //Move the enemies WARN: inefficient to delete element of vector
    for(size_t i = 0; i < enemies.size(); ++i){
        enemies[i].move(0.f, 2.5f);
        // Check if clicked on
        if(!mouseHeld){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(enemies[i].getGlobalBounds().contains(mousePosView)){
                    mouseHeld = true;
                    enemies.erase(enemies.begin() + i);
                    ++points;
                    if(points>best) best=points;
                    continue;
                }
            }
        }
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseHeld = false;
        // Check if below screen
        if(enemies[i].getPosition().y > window->getSize().y){
            enemies.erase(enemies.begin() + i);
            points = 0;
        }
    }
}
void Game::renderEnemies(){
    for(auto &e : enemies){
        window->draw(e);
    }
}

void Game::updateText(){
    currentText.setString(std::to_string(points));
    bestText.setString("Best: "+std::to_string(best));
}
void Game::renderText(){
    window->draw(currentText);
    window->draw(bestText);
}