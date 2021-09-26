#include "../globals.h"

#include <SFML/Graphics.hpp>

namespace scene{
    class Default{
        public:
            void init();
            void render();
            void update();
        private:
            void updateBox();
            sf::RectangleShape box;
            sf::Vector2f boxPos;
            bool boxDirection;
    };
}