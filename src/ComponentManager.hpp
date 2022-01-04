#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP
#include "Component.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class ComponentManager {
public:
    ~ComponentManager();
    std::vector<Component*> components;
    Component* addToggle(sf::Vector2f pos, bool s);
    Component* addBixle(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    void press(sf::RenderWindow &window);
    void release();

    std::vector<Plug*> connections;
    void addConnection(Plug *in, Plug *out);
};

#endif