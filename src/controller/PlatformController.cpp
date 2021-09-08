//
// Created by ivan on 13.08.2021.
//

#include "controller/PlatformController.h"
#include "core/Logic.h"

float PlatformController::x() const {
    return platform->getPosition().x;
}

float PlatformController::y () const {
    return platform->getPosition().y;
}

void PlatformController::update() {
    platform->move(speed);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
        setSpeedX(-Logic::PLATFORM_SPEED);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&right() < Logic::WINDOW_WIDTH)
        setSpeedX(Logic::PLATFORM_SPEED);
    else
        setSpeedX(0);
}

float PlatformController::left() const {
    return x() - platform->getSize().x / 2.f;
}

float PlatformController::right() const{
    return x() + platform->getSize().x / 2.f;
}

float PlatformController::top() const {
    return y() - platform->getSize().y / 2.f;
}

float PlatformController::bottom() const {
    return y() + platform->getSize().y / 2.f;
}

PlatformController::PlatformController() {
    auto shape = sf::Vector2f(Logic::PLATFORM_WIDTH, Logic::PLATFORM_HEIGHT);
    platform = std::make_unique<Platform>(shape);
    speed = sf::Vector2f(-Logic::PLATFORM_SPEED, 0);
}

void PlatformController::setSpeedX(float x) {
    speed.x = x;
}
