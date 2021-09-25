#include "game.h"
// Private Functions
void Game::initVariables(){
    this->window = nullptr;
    rightPressed = leftPressed = downPressed = upPressed = false;
    clock.restart(); // might not be needed
    deltaClock.restart();
    delta = millis = 0;

    // Player
    box.setSize(sf::Vector2f(50.f,50.f));
    boxPos = sf::Vector2f(0.f,0.f);
    boxDirection = false;
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
    inputText.setString("");
    inputText.setFont(font);
    inputPosition = -10.f;
    inputText.setPosition(sf::Vector2f(20, 0));
    outputText.setString(">\n");
    outputText.setFont(font);
    outputPostion = -10.f;
    outputText.setPosition(sf::Vector2f(0, 0));
}
void Game::initWindow(){
    //this->videomode.height = 1080;//600;
    //this->videomode.width = 1920;//800;
    this->window = new sf::RenderWindow(this->videomode.getDesktopMode(), "Java minus minus", sf::Style::Fullscreen | sf::Style::Close);

    this->window->setFramerateLimit(145);
}
void Game::initFonts(){
    if(!this->font.loadFromFile("fonts/LiberationMono-Bold.ttf"))std::cerr<<"ERROR::GAME::INITFONTS::Failed to load font LiberationMono-Bold.tff\n";
}
void Game::initText(){

}

// CONSTRUCTORS
Game::Game() /*: clock(&Game::tick, this)*/{
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
                break;
            case sf::Event::KeyPressed:
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
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
    // Switch over command
    if(!word.compare("exit"))std::exit(0);
    else if(!word.compare("echo")){
        std::string temp;
        while(stream>>word)temp += word + ' ';
        updateTTY(temp);
    }
    else if(!word.compare("clear")){
        output = "";
        outputPostion = inputPosition = 0.f;
    }
    else{ // Default case
        updateTTY(word+": command not found");
    }
}
void Game::updateTTY(std::string out){
    output = output + "> " + input + '\n' + out + '\n';
    if(inputPosition <= 1000)inputPosition += 60;
    else{
        outputPostion -= 60;
    }
}

/** Sets flags based on time elapsed */
void Game::tick(){
    millis = clock.getElapsedTime().asMilliseconds();
    //tock += static_cast<unsigned int>(clock.getElapsedTime().asSeconds()*256); // 0-255 in almost exactly 1 second
    //tock += clock.getElapsedTime().asMilliseconds()>>2; // 0-255 in 1024 ms
}

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

// PUBLIC
// UPDATE
void Game::update() {
    tick();
    // Game Objects
    //updateBox();

    pollEvents();

    updateMousePositions();

    updateText();
}

void Game::render() {
    deltaClock.restart(); // Begin deltaTimer
    // Clear
    window->clear();

    // Render
    //renderBox(); // Test of animation pipeline
    renderTestSprite();

    // UI
    renderText();

    // Display
    window->display();

    // Calculate time
    delta = deltaClock.getElapsedTime().asSeconds();
}

void Game::updateMousePositions(){
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateText(){
    inputText.setPosition(sf::Vector2f(30.f,inputPosition));
    outputText.setPosition(sf::Vector2f(0.f,outputPostion));
}
void Game::renderText(){
    inputText.setString(input);
    window->draw(inputText);
    outputText.setString(output+">\n");
    window->draw(outputText);
}

// Game Objects
