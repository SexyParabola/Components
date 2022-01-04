// main.cpp -- i3 Floater Window
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "i3window.hpp"
#include <math.h>

const sf::Color rainColor(const double theta) {
    sf::Color c;
    c.r = ((sin(theta) + 1.0) / 2.0) * 255;
    c.g = ((sin(theta + 2.094393) + 1.0) / 2.0) * 255;
    c.b = ((sin(theta + 4.188786) + 1.0) / 2.0) * 255;
    return c;
}



int main()
{
    sf::Clock clock;
    sf::Time tickTimer = clock.getElapsedTime();
    sf::RenderWindow window(sf::VideoMode(2400, 1600), "i3-f");
    window.setPosition(sf::Vector2i(250, 65));
    i3Window windowBar(window, "Components");

    ComponentManager cm;

    ToggleComponent* tog1 = (ToggleComponent*)cm.addToggle(sf::Vector2f(200, 200), false);

    ToggleComponent* tog2 = (ToggleComponent*)cm.addToggle(sf::Vector2f(200, 600), true);

    BixleComponent* bix1 = (BixleComponent*)cm.addBixle(sf::Vector2f(500, 400));
    BixleComponent* bix2 = (BixleComponent*)cm.addBixle(sf::Vector2f(500, 600));

    cm.addConnection(tog1->getStatePlug(), bix1->getStatePlug());
    cm.addConnection(tog1->getStatePlug(), bix2->getStatePlug());


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    windowBar.press();
                    cm.press(window);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    windowBar.release();
                    cm.release();
                }
            }
        }
        if (clock.getElapsedTime().asSeconds() - tickTimer.asSeconds() > 0.016) {
            tickTimer = clock.getElapsedTime();
            windowBar.tick();
        }

        window.clear(sf::Color(35, 25, 35));
        cm.draw(window);
        windowBar.draw();
        window.display();
        }

    return 0;
} 
