// i3window.hpp -- Linux i3 Floater Window Test
#ifndef I3WINDOW_H
#define I3WINDOW_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class i3Window {
    private:
    sf::Clock clock;
    sf::Time grabTimer = clock.getElapsedTime();
    sf::RenderWindow* window = NULL;
    Button* exitButton = NULL;
    Button* windowBar = NULL;
    sf::Vector2i windowAnchor;
    sf::Vector2i mouseAnchor;
    bool grab = false;
    public:
    const int w = 20;
    i3Window(sf::RenderWindow &Window, std::string title);
    ~i3Window();
    void press();
    void release();
    void tick();
    void draw();
    sf::RenderWindow& get();
};

#endif

