// i3window.hpp -- Linux i3 Floater Window Test
#include "i3window.hpp"

i3Window::i3Window(sf::RenderWindow &Window, std::string title) {
    window = &Window;
    window->setTitle(title);
    windowBar = new Button(sf::Vector2f(0, 0), sf::Vector2f(window->getSize().x, w), sf::Color(200, 200, 200));
    window->setSize(sf::Vector2u(window->getSize().x, window->getSize().y + w));
    exitButton = new Button(sf::Vector2f(window->getSize().x - w, 5), sf::Vector2f(10, 10));
    exitButton->rect.setOutlineColor(sf::Color::Black);
    exitButton->rect.setOutlineThickness(1);
}
i3Window::~i3Window() {
    delete windowBar;
    delete exitButton;
}
void i3Window::press() {
    if (windowBar->press(*window)) {
        grab = true;
        windowAnchor = window->getPosition();
        mouseAnchor = sf::Mouse::getPosition();
    }
    if (exitButton->press(*window))
        window->close();
}
void i3Window::release() {
    grab = false;
    exitButton->release();
}
void i3Window::tick() {
    if (clock.getElapsedTime().asSeconds() - grabTimer.asSeconds() > 0.016 && grab) {
        grabTimer = clock.getElapsedTime();
        sf::Vector2i temp;
        temp.x = windowAnchor.x + (sf::Mouse::getPosition().x - mouseAnchor.x);
        temp.y = windowAnchor.y + (sf::Mouse::getPosition().y - mouseAnchor.y);
        window->setPosition(temp);
    }
}
void i3Window::draw() {
    windowBar->draw(*window);
    exitButton->draw(*window);
};
sf::RenderWindow& i3Window::get() {
    return *window;
};
