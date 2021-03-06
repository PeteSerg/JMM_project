#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#pragma once
enum class Scene {Default, Menu, TextBased, Lvl};

/** Loads game tree from file specified in tree directory */
extern std::string treeFileName;
extern Scene currentScene;
/** Render window. WARN: Can only be referenced by main thread */
extern sf::RenderWindow *window;
extern sf::VideoMode videomode;
/** Milliseconds since start of program. Used for cyclic operations. Updated every cycle */
extern uint32_t millis;
/** Seconds since last update */
extern float delta;
/** State of keyboard keys */
extern bool rightPressed, leftPressed, downPressed, upPressed;
/** State of mouse clicks */
extern bool leftClick;
/** Position of mouse relative to window */
extern sf::Vector2i mousePosWindow;
/** Position of mouse on screen */
extern sf::Vector2f mousePosView;
