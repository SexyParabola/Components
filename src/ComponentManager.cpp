#include "ComponentManager.hpp"
#include "Button.hpp"
#include "Component.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Component* ComponentManager::addToggle(sf::Vector2f pos, bool s) {
    Component* cassi = new ToggleComponent(pos, s);
    components.push_back(cassi);
    return cassi;
}

Component* ComponentManager::addBixle(sf::Vector2f pos) {
    Component* cassi = new BixleComponent(pos);
    components.push_back(cassi);
    return cassi;
}

ComponentManager::~ComponentManager() {
    for (unsigned int i = 0; i < components.size(); i++) {
        delete components[i];
    }
}

void ComponentManager::draw(sf::RenderWindow &window) {
    //tickConnections();
    for (unsigned int i = 0; i < components.size(); i++) {
        ((Component*)components[i])->draw(window);
    }
    BarShape bar;
    bar.width = 4;
    bar.rect.setFillColor(sf::Color::Magenta);
    for (unsigned int i = 0; i < connections.size(); i++) {
        bar.pos1 = connections[i]->pos;
        bar.pos2 = connections[i]->connection->pos;
        bar.update();
        window.draw(bar.rect);
        //std::cout << bar.pos1.x << ", " << bar.pos1.y << " | " << bar.pos2.x << ", " << bar.pos2.y << std::endl;
    }
}

void ComponentManager::press(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        ((Component*)components[i])->press(window);
    }
}

void ComponentManager::release() {
    for (unsigned int i = 0; i < components.size(); i++) {
        ((Component*)components[i])->release();
    }
}

void ComponentManager::addConnection(Plug* in, Plug* out) {
    in->connection = out;
    out->connection = in;
    out->data = in->data;
    connections.push_back(out);
}
