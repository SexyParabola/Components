#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Component {
protected:
    sf::RectangleShape pallet;
private:
    Button bar;
    sf::Vector2f anchor;
    sf::Vector2i clickAnchor;
    sf::Vector2i clickVector;
public:
    explicit Component(sf::Vector2f pos, sf::Vector2f size);
    void drawPallet(sf::RenderWindow &window);
    void barPress(sf::RenderWindow &window);
    void barRelease();
    virtual void draw(sf::RenderWindow &window);
    virtual void press(sf::RenderWindow &window);
    virtual void release();
};


struct Plug {
    sf::Vector2f pos;
    void* data = nullptr;
    Plug* connection = nullptr;
};


class IOComponent : public Component {
protected:
    Plug plug;
    Button statePlug;
    Button button;
public:
    IOComponent(sf::Vector2f pos);
    void drawIO(sf::RenderWindow &window);
    void pressIO(sf::RenderWindow &window);
    void releaseIO();
    Plug* getStatePlug();
};

class ToggleComponent : public IOComponent {
public:
    bool state;
    ToggleComponent(sf::Vector2f pos, bool s);
    void draw(sf::RenderWindow &window);
    void press(sf::RenderWindow &window);
    void release();
};

class BixleComponent : public IOComponent {

public:
    BixleComponent(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    void press(sf::RenderWindow &window);
    void release();
};

#endif