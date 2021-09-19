#include "game.h"
// Private Functions
void Game::initVariables(){
    this->window = nullptr;
    rightPressed = leftPressed = downPressed = upPressed = false;
    clock.launch();
    exit = false;

    tickTime = 20; // 20 millis
    hasMovedThisTick = false;
    moveTimeOut = 0;

    // Player
    playerPos = sf::Vector2f(10.f, 40.f);
    playerLast = playerPos;
    player.setPosition(playerPos);
    player.setSize(sf::Vector2f(50.f, 50.f));
}
void Game::initWindow(){
    //this->videomode.height = 1080;//600;
    //this->videomode.width = 1920;//800;
    this->window = new sf::RenderWindow(this->videomode.getDesktopMode(), "Java minus minus", sf::Style::Fullscreen | sf::Style::Close);

    this->window->setFramerateLimit(144);
}
void Game::initFonts(){
    if(!this->font.loadFromFile("fonts/LiberationMono-Bold.ttf"))std::cerr<<"ERROR::GAME::INITFONTS::Failed to load font LiberationMono-Bold.tff\n";
}
void Game::initText(){

}

// CONSTRUCTORS
Game::Game() : clock(&Game::tick, this){
    this->initVariables();
    this->initWindow();
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
                exit = true;
                break;
            case sf::Event::KeyPressed:
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
                        exit = true;
                        break;
                    case sf::Keyboard::Right:
                        rightPressed = true;
                        if(leftPressed || hasMovedThisTick) break;
                        // hasMovedThisTick = true;
                        // playerPos.x += 50.f;
                        // if(downPressed && !upPressed) playerPos.y += 50.f;
                        // else if(upPressed) playerPos.y -= 50.f;
                        break;
                    case sf::Keyboard::Left:
                        leftPressed = true;
                        if(rightPressed || hasMovedThisTick) break;
                        // hasMovedThisTick = true;
                        // playerPos.x -= 50.f;
                        // if(downPressed && !upPressed) playerPos.y += 50.f;
                        // else if(upPressed) playerPos.y -= 50.f;
                        break;
                    case sf::Keyboard::Down:
                        downPressed = true;
                        if(upPressed || hasMovedThisTick) break;
                        // hasMovedThisTick = true;
                        // playerPos.y += 50.f;
                        // if(rightPressed && !leftPressed) playerPos.x += 50.f;
                        // else if(leftPressed) playerPos.x -= 50.f;
                        break;
                    case sf::Keyboard::Up:
                        upPressed = true;
                        if(downPressed || hasMovedThisTick) break;
                        // hasMovedThisTick = true;
                        // playerPos.y -= 50.f;
                        // if(rightPressed && !leftPressed) playerPos.x += 50.f;
                        // else if(leftPressed) playerPos.x -= 50.f;
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch(this->ev.key.code){
                    case sf::Keyboard::Right:
                        rightPressed = false; break;
                    case sf::Keyboard::Left:
                        leftPressed = false; break;
                    case sf::Keyboard::Down:
                        downPressed = false; break;
                    case sf::Keyboard::Up:
                        upPressed = false; break;
                }
                break;
        }
    }
}

void Game::tick(){
    while(!exit){
        if(timer.getElapsedTime().asMilliseconds()>moveTimeOut)
        hasMovedThisTick = false;
        sf::sleep(sf::milliseconds(tickTime));
        //sf::sleep(sf::milliseconds(tickTime));
    }
}

// PUBLIC
// UPDATE
void Game::update() {
    //tick();
    pollEvents();

    updateMousePositions();
    updatePlayer();

    updateText();
}

void Game::render() {
    // Clear
    window->clear();

    // Render
    renderPlayer();

    // UI
    renderText();

    // Display
    window->display();
}

void Game::updateMousePositions(){
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateText(){

}
void Game::renderText(){

}

// Game Objects
void Game::updatePlayer(){
    if(!hasMovedThisTick){
        if(rightPressed && !leftPressed) {playerLast = playerPos;playerPos.x += 50.f;hasMovedThisTick=true;moveTimeOut = timer.getElapsedTime().asMilliseconds()+250;}
        else if(leftPressed /*&& !rightPressed*/) {playerLast = playerPos;playerPos.x -= 50.f;hasMovedThisTick=true;moveTimeOut = timer.getElapsedTime().asMilliseconds()+250;}
        else if(downPressed /*&& !upPressed*/) {playerLast = playerPos;playerPos.y += 50.f;hasMovedThisTick=true;moveTimeOut = timer.getElapsedTime().asMilliseconds()+250;}
        else if(upPressed /*&& !downPressed*/) {playerLast = playerPos;playerPos.y -= 50.f;hasMovedThisTick=true;moveTimeOut = timer.getElapsedTime().asMilliseconds()+250;}
        //player.setPosition(playerPos);
    }
}
void Game::renderPlayer(){
    float ratio = 1 - static_cast<float>(moveTimeOut-timer.getElapsedTime().asMilliseconds())/250;
    if(timer.getElapsedTime().asMilliseconds()<=moveTimeOut){
        //std::cout<<ratio<<"\n";
        player.setPosition(playerLast.x+(playerPos.x-playerLast.x)*ratio, playerLast.y+(playerPos.y-playerLast.y)*ratio);
    }
    //else player.setPosition(playerPos);
    window->draw(player);
}