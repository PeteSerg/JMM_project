
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/** Render window. WARN: Can only be referenced by main thread */
extern sf::RenderWindow *window;
extern sf::VideoMode videomode;
/** Milliseconds since start of program. Used for cyclic operations. Updated every cycle */
extern uint32_t millis;
/** Seconds since last update */
extern float delta;