// THIS IS A TEST OF SFML for 2D graphics
// g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 500), "My window");

    // Load texture
    sf::Texture texture;
    if (!texture.loadFromFile("texture.png"))
    {
        std::cerr<<"BRUH what did you do with texture.png\n";
        exit(0);
    }
    texture.setSmooth(true);

    // Sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    //texture.setRepeated(true);
    //sprite.setTextureRect(sf::IntRect(200, 200, 64, 64)); // Sample texture
    //sprite.setColor(sf::Color(0, 255, 0)); // green

    // Text
    sf::Font font;
    if(!font.loadFromFile("./LiberationSerif-Regular.ttf")){
        std::cout<<"BRUH WHERE DID YOU PUT THE FONT\n";
        exit(0);
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Press G for Bread Man");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(100, 200);
    sf::Text text2;
    text2.setFont(font);
    text2.setString("interactive media");
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::Red);

    //Shape
    sf::CircleShape shape(50.f);
    shape.setPosition(300,100);

    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        window.draw(sprite);
        window.draw(text);
        window.draw(text2);
        window.draw(shape);

        // end the current frame
        window.display();
    }

    return 0;
}