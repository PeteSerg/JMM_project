#include "menu.h"

Menu::Menu(float width, float height)
{
    /*if(!font.loadFromFile("arial.ttf"))
    {
        //Handle error
    }*/

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::white);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::white);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    selectedItemIndex = 0;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if(selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor(sf::Color::white);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::red);
    }
}

void Menu::moveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(sf::Color::white);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::red);
    }
}

void Menu::runWhile()
{
    switch(event.type)
    {
        case sf::Event::KeyReleased:
            switch(event.key.code)
            {
                case sf::Keyboard::Up;
                menu.moveUp();
                break;

                case sf::Keyboard::Down;
                menu.moveDown();
                break;

                case sf::Keyboard::Return;
                    switch(menu.getPressedItem())
                    {
                        case 0:
                            std::cout<<"Play button pressed"<<std::endl;
                            break;
                        case 1:
                            std::cout<<"Options button pressed"<<std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                    }

                    break;
            }

            break;
        case sf::Event::Closed:
            window.close();

            break;            
    }
}