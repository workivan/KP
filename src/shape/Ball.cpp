//
// Created by ivan on 17.08.2021.
//

#include "shape/Ball.h"
#include <core/Logic.h>

Ball::Ball(float radius): sf::CircleShape(radius) {
    setFillColor(sf::Color::White);
    setPosition(Logic::BALL_DEFAULT_POSITION);
    setOrigin(radius, radius);
};
