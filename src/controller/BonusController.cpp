//
// Created by ivan on 30.08.2021.
//

#include <SFML/Graphics.hpp>
#include "controller/BonusController.h"
#include "core/Logic.h"

float BonusController::x() const {
    return bonus->getPosition().x;
}

float BonusController::y() const {
    return bonus->getPosition().y;
}

float BonusController::left() const {
    return x() - bonus->getSize().x / 2.f;
}

float BonusController::right() const {
    return x() + bonus->getSize().x / 2.f;
}

float BonusController::top() const {
    return y() - bonus->getSize().y / 2.f;
}

float BonusController::bottom() const {
    return y() + bonus->getSize().y / 2.f;
}

BonusController::BonusController(const sf::Vector2f &pos, float speedf, BlockControllerSupport::HiredType & hiredType){
    auto shape = sf::Vector2f(Logic::BONUS_WIDTH, Logic::BONUS_HEIGHT);
    bonus = std::make_unique<Bonus>(pos, shape);
    speed = sf::Vector2f(0, speedf);
    type = hiredType;
}

void BonusController::update() {
    bonus->move(speed);
}

BlockControllerSupport::HiredType BonusController::getType() const {
    return type;
}

const Bonus &BonusController::getBonus() const {
    return *bonus;
}

bool BonusController::isExpired() const {
    return expired;
}

void BonusController::setExpired(bool expired) {
    BonusController::expired = expired;
}
