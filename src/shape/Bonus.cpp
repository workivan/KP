//
// Created by ivan on 30.08.2021.
//

#include <core/Logic.h>
#include "shape/Bonus.h"

Bonus::Bonus(const sf::Vector2f& pos,  const sf::Vector2f& shape) : RectangleShape(shape) {
    setOrigin(Logic::BONUS_WIDTH/ 2.f, Logic::BONUS_HEIGHT/2.f);
    setFillColor(sf::Color::Yellow);
    setPosition(pos);
}
