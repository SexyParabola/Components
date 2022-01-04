#include "Component.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#define BAR_SIZE 20

#define BAR_BASE_COLOR 80, 80, 85
#define BAR_PRESS_COLOR 100, 100, 100

Component::Component(sf::Vector2f pos, sf::Vector2f size) {
    anchor = pos;
    pallet.setPosition(pos.x, pos.y);
    pallet.setSize(size); // -- Temp size --
    pallet.setFillColor(sf::Color(128, 128, 150));
    pallet.setOutlineThickness(1);
    pallet.setOutlineColor(sf::Color::Black);
    bar.rect.setPosition(pos.x, pos.y - BAR_SIZE);
    bar.rect.setSize(sf::Vector2f(size.x, BAR_SIZE));
    bar.rect.setOutlineThickness(1);
    bar.rect.setOutlineColor(sf::Color::Black);
    bar.rect.setFillColor(sf::Color(BAR_BASE_COLOR));
    //std::cout << "Pallet INIT\n";
}

void Component::drawPallet(sf::RenderWindow &window) {
    sf::Vector2f offset(sf::Mouse::getPosition(window).x - clickAnchor.x, sf::Mouse::getPosition(window).y - clickAnchor.y);
    if (bar.getPressed()) {
        pallet.setPosition(anchor.x + offset.x, anchor.y + offset.y);
    }
    if (pallet.getPosition().y < BAR_SIZE + 20) pallet.setPosition(pallet.getPosition().x, BAR_SIZE + 20);
    if (pallet.getPosition().x < 0) pallet.setPosition(0, pallet.getPosition().y);
    if (pallet.getPosition().x + pallet.getSize().x > window.getSize().x) pallet.setPosition(window.getSize().x - pallet.getSize().x, pallet.getPosition().y);
    if (pallet.getPosition().y + pallet.getSize().y + BAR_SIZE > window.getSize().y) pallet.setPosition(pallet.getPosition().x, window.getSize().y - pallet.getSize().y - BAR_SIZE);
    bar.rect.setPosition(pallet.getPosition().x, pallet.getPosition().y - BAR_SIZE);
    window.draw(pallet);
    window.draw(bar.rect);
}

void Component::barPress(sf::RenderWindow &window) {
    if(bar.press(window, sf::Color(BAR_PRESS_COLOR))) {
        anchor = pallet.getPosition();
        clickAnchor = sf::Mouse::getPosition(window);
    }
}

void Component::barRelease() {
    bar.release(sf::Color(BAR_BASE_COLOR));
}

void Component::draw(sf::RenderWindow &window) {
    drawPallet(window);
}

void Component::press(sf::RenderWindow &window) {
    barPress(window);
}

void Component::release() {
    barRelease();
}

// -----------------

IOComponent::IOComponent(sf::Vector2f pos) : Component(pos, sf::Vector2f(160, 140)) {
    //button.rect.setPosition(sf::Vector2f(pallet.getPosition().x + 20, pallet.getPosition().y + 20));
    button.rect.setSize(sf::Vector2f(100, 100));
    button.rect.setOutlineThickness(2);
    button.rect.setOutlineColor(sf::Color(255, 102, 102));
    statePlug.rect.setSize(sf::Vector2f(10, 10));
    statePlug.rect.setFillColor(sf::Color::Blue);
    statePlug.rect.setOutlineColor(sf::Color::Black);
    statePlug.rect.setOutlineThickness(2);
    //std::cout << "Button INIT\n";
}

void IOComponent::drawIO(sf::RenderWindow &window) {
    plug.pos = sf::Vector2f(statePlug.rect.getPosition().x + 5, statePlug.rect.getPosition().y + 5);
    const sf::Vector2f pos = pallet.getPosition();
    drawPallet(window);
    window.draw(button.rect);
    window.draw(statePlug.rect);
}

void IOComponent::pressIO(sf::RenderWindow &window) {
    barPress(window);
    statePlug.press(window);
    //if (button.press(window)) state = !state;
}

void IOComponent::releaseIO() {
    barRelease();
    button.release();
    statePlug.release();
}

Plug* IOComponent::getStatePlug() {
    return &plug;
}

// -----------------

ToggleComponent::ToggleComponent(sf::Vector2f pos, bool s) : IOComponent(pos) {
    state = s;
    plug.data = &state;
    statePlug.rect.setFillColor(sf::Color::Red);
}

void ToggleComponent::draw(sf::RenderWindow &window) {
    const sf::Vector2f pos = pallet.getPosition();
    button.rect.setPosition(sf::Vector2f(pos.x + 20, pos.y + 20));
    statePlug.rect.setPosition(sf::Vector2f(pos.x + 135, pos.y + 70));
    button.rect.setFillColor(state ? sf::Color::White : sf::Color::Black);
    drawIO(window);
}

void ToggleComponent::press(sf::RenderWindow &window) {
    if (button.press(window)) state = !state;
    pressIO(window);
}

void ToggleComponent::release() { releaseIO(); }



// -----------------

BixleComponent::BixleComponent(sf::Vector2f pos) : IOComponent(pos) {}

void BixleComponent::draw(sf::RenderWindow &window) {
    const sf::Vector2f pos = pallet.getPosition();
    button.rect.setPosition(sf::Vector2f(pos.x + 40, pos.y + 20));
    statePlug.rect.setPosition(sf::Vector2f(pos.x + 15, pos.y + 70));
    if (plug.data == nullptr) {
        button.rect.setFillColor(sf::Color::Red);
    } else {
        button.rect.setFillColor( *((bool*)plug.data) ? sf::Color::White : sf::Color::Black);
    }
    drawIO(window);
}

void BixleComponent::press(sf::RenderWindow &window) { pressIO(window); }

void BixleComponent::release() { releaseIO(); }