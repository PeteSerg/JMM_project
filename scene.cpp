// first attempt

#include "scene.h"

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

/** Pass scene by parameter */
Scene::Scene(sf::RenderWindow *window, std::vector<sf::Texture> &textures, 
              std::vector<sf::Sprite> &sprites, std::vector<sf::Text> &text, std::vector<sf::CircleShape> shapes){
    Scene::window = window;
    Scene::filename = "";
    Scene::textures = textures;
    Scene::sprites = sprites;
    Scene::text = text;
    Scene::shapes = shapes;
}

/** Load scene from file */
Scene::Scene(std::string filename, sf::RenderWindow *window){
    Scene::window = window;
    Scene::filename = filename;

    std::ifstream file;
    file.open(filename);
    if(file.fail()){
        std::cerr<<"Scene file \""<<filename<<"\" could not be opened. Exiting.\n";
        exit(EXIT_FAILURE);
    }
    size_t line = 1;
    std::string next;
    while(std::getline(file, next, '\n')){
        if(next.size()==0) error("", line, "Empty line");
        switch(next[0]){ // TODO implement other types
            case 'S':
                loadShape(next, line);
                break;
            default:
                error(next, line, next.substr(0,1));
        }
        ++line;
    }
}

void Scene::draw(){
    for(size_t i=0; i<shapes.size(); i++){
        window->draw(shapes[i]);
    }
}

void Scene::loadShape(std::string next, size_t line){ // TODO implement other shapes
    std::stringstream stream(next);
    stream.ignore(256, ' ');
    switch(next[1]){
        case 'C': // CIRCLE
            {
            float fl1, fl2;
            if(!(stream>>fl1))error(next, line, "Radius"); // Radius
            sf::CircleShape shape(fl1);
            if(!(stream>>fl1>>fl2))error(next, line, "Position"); // Position
            shape.setPosition(fl1, fl2);
            shapes.push_back(shape);
            }
            break;
        default:
            error(next, line, next.substr(1,2));
    }
}

void Scene::error(std::string next, size_t line, std::string err){
    std::cerr<<"ERROR: "<<filename<<" could not be parsed.\n";
    std::cerr<<"At line "<<line<<":\t"<<next<<"\n"<<err<<" is invalid.\n";
    exit(EXIT_FAILURE);
}