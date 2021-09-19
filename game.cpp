#include "game.h"
// Private Functions
void Game::initVariables(){
    this->window = nullptr;
    rightPressed = leftPressed = downPressed = upPressed = false;
    clock.launch();
    exit = false;

    wait = 4; // 20 millis

    // Player
    box.setSize(sf::Vector2f(50.f,50.f));
    boxPos = sf::Vector2f(0.f,0.f);
    if(!testTexture.loadFromFile("spritetest.png")){
        std::cout<<"Could not load sprite texture from file";
        std::exit(0);
    }
    testSprite.setTexture(testTexture);
    testSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    testSprite.setScale(10,10);//290, 710
    testSprite.setPosition(710, 290);

    // Text
    if(!font.loadFromFile("fonts/UbuntuMono-R.ttf")){
        std::cout<<"Could not load font from file";
        std::exit(0);
    }
    currentText.setString(">");
    currentText.setFont(font);
    bestText.setString("");
    bestText.setFont(font);
    bestText.setPosition(sf::Vector2f(20, 0));
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
                        break;
                    case sf::Keyboard::Left:
                        leftPressed = true;
                        break;
                    case sf::Keyboard::Down:
                        downPressed = true;
                        break;
                    case sf::Keyboard::Up:
                        upPressed = true;
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
            case sf::Event::TextEntered:
                if(ev.text.unicode < 128){
                    if(ev.text.unicode == 8){ // backspace
                        if(input.size()>0) input.pop_back();
                    } else if(ev.text.unicode == 13){ // carriage return
                        execute(input);
                        input = "";
                    } else if(input.size()>40) break; // Enforce string length limit
                    else input += static_cast<char>(ev.text.unicode);
                }
        }
    }
}

void Game::execute(std::string command){
    std::stringstream stream(command);
    std::string word;
    stream>>word;
    if(!word.compare("exit")) std::exit(0);
    if(!word.compare("stop")) exit=true;
}


/** Sets flags based on time elapsed */
void Game::tick(){
    while(!exit){
        ++tock; // Overflows to zero after 255
        animationTick();
        sf::sleep(sf::milliseconds(wait));
    }
}
// 8 animation ticks/second
void Game::animationTick(){
    if(tock<=32){
        animTick = 0;
    }else if(tock<=64){
        animTick = 1;
    }else if(tock<=96){
        animTick = 2;
    }else if(tock<=128){
        animTick = 3;
    }else if(tock<=160){
        animTick = 4;
    }else if(tock<=192){
        animTick = 5;
    }else if(tock<=224){
        animTick = 6;
    }else{ //if(tock<=256){
        animTick = 7;
    }
}

void Game::renderBox(){
    box.setPosition(boxPos.x + animTick*1.f - 2.f*(animTick-4)*(animTick>3),boxPos.y);
    window->draw(box);
}
void Game::renderTestSprite(){
    testSprite.setTextureRect(sf::IntRect(0, animTick*50, 50, 50));
    window->draw(testSprite);
}

// PUBLIC
// UPDATE
void Game::update() {
    //tick();
    pollEvents();

    updateMousePositions();

    updateText();
}

void Game::render() {
    // Clear
    window->clear();

    // Render
    //renderBox(); // Test of animation pipeline
    renderTestSprite();

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
    window->draw(currentText);
    bestText.setString(input);
    window->draw(bestText);
}

// Game Objects
