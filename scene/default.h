#include "../globals.h"

/** Other scenes can be made based of of this default scene.
 *  This class demonstrates initializing, updating, and rendering sprites and text.
 * */
namespace scene{
    class Default{
        public:
            /** The default scene is initalized immediately.
             *  Other scenes should only be initialized before they are used */
            void init();
            /** Every scene implements a render function.
             *  Classes currently draw directly to the window */
            void render();
            /** Every scene should also implement an update fuction
             *  Update handles the game state at any moment */
            void update();
        private:
            // These are called internally by update() and render() respectively
            void updateBox();
            void renderSprite();
            // Moving rect using delta
            sf::RectangleShape box;
            sf::Vector2f boxPos;
            // Animated sprite using millis
            sf::Texture texture;
            sf::Sprite sprite;
            // Warning text
            sf::Font ubuntuMono;
            sf::Text warn;
    };
}