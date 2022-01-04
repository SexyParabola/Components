#ifndef i3BUTTON_H
#define i3BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
private:
    sf::Clock clock;
    sf::Time timer;
    bool pressed = false;
public:
    sf::RectangleShape rect;
    Button();
    Button(sf::Vector2f pos, sf::Vector2f size);
    Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
    void draw(sf::RenderWindow &window);
    void setOrigin(sf::Vector2f Origin);
    bool press(sf::RenderWindow &window, sf::Color color); // Checks if mouse is over button && sets color if TRUE
    bool press(sf::RenderWindow &window); // Checks if mouse is over button
    void release(sf::Color color);
    void release();
    bool getPressed();
};

struct BarShape {
    BarShape();
    BarShape(sf::Vector2f p1, sf::Vector2f p2, float w);
    void update();
    float width;
    sf::Vector2f pos1, pos2, uvec;
    sf::RectangleShape rect; 
};


#endif