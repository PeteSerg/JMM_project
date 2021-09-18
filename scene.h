// First attempt

#include <SFML/Graphics.hpp>

#include <vector>

class Scene{
    public:
        /** Create scene. Send vectors to scene **/
        Scene(sf::RenderWindow *window, std::vector<sf::Texture> &textures, 
              std::vector<sf::Sprite> &sprites, std::vector<sf::Text> &text, std::vector<sf::CircleShape> shapes);
        /** Load scene from datafile NOT IMPLEMENTED */
        Scene(std::string filename, sf::RenderWindow *window);
        /** Draw scene */
        void draw();
        /** Disable sprite at index */
        void disSprite(size_t index);
        /** Disable text at index */
        void disText(size_t index);
        /** Disable shape at index */
        void disShape(size_t index);

        std::string filename;
    private:
        void loadShape(std::string next, size_t line);
        void error(std::string next, size_t line, std::string err);

        sf::RenderWindow *window;
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite> sprites;
        std::vector<sf::Text> text;
        std::vector<sf::CircleShape> shapes;
};