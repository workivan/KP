//
// Created by ikuzin on 06.06.2021.
//

#ifndef KP_WINDOW_H
#define KP_WINDOW_H

#include "SFML/Graphics.hpp"
#include "Logic.h"

class Window : public sf::Drawable, public sf::Transformable {
private:
    sf::RenderWindow screen;
    std::shared_ptr<Logic> state;
public:
    Window() : state(std::make_shared<Logic>()) {
        screen.create(sf::VideoMode(Logic::WINDOW_WIDTH, Logic::WINDOW_HEIGHT), "Arkanoid");
        screen.setFramerateLimit(60);
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RenderWindow &getScreen() { return screen; }
public:
    void stateUpdate();
    void render();
};


#endif //KP_WINDOW_H
