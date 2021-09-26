#include "default.h"

namespace scene{
    void Default::init(){
        box.setSize(sf::Vector2f(50.f,50.f));
        boxPos = sf::Vector2f(0.f,0.f);
        boxDirection = false;
    }
    void Default::render(){
        box.setPosition(boxPos.x,boxPos.y);
        window->draw(box);
    }
    void Default::update(){
        updateBox();
    }

    // Box
    void Default::updateBox(){
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
}