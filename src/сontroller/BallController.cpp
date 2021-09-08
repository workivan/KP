//
// Created by ivan on 12.08.2021.
//
#include <controller/BallController.h>
#include "core/Logic.h"

float BallController::left() const {
    return x() - ball->getRadius();
}

float BallController::right() const {
    return x() + ball->getRadius();
}

float BallController::top() const {
    return y() - ball->getRadius();
}

float BallController::bottom() const {
    return y() + ball->getRadius();
}

float BallController::x() const {
    return ball->getPosition().x;
}

float BallController::y() const {
    return ball->getPosition().y;
}

void BallController::update() {
    if (isActive()) {
        ball->move(speed);
        auto bspeed = Logic::getBallSpeed();
        if (left() < 0)
            setSpeedX(bspeed);
        else if (right() > Logic::WINDOW_WIDTH)
            setSpeedX(-bspeed);
        if (top() < 0)
            setSpeedY(bspeed);
        else if (bottom() > Logic::WINDOW_HEIGHT)
            setSpeedY(-bspeed);
    }
}

BallController::BallController(bool isActive) {
    ball = std::make_unique<Ball>(Logic::BALL_RADIUS);
    auto bspeed = Logic::getBallSpeed();
    speed = sf::Vector2f(-bspeed, -bspeed);
    active = isActive;
}

void BallController::setSpeedX(float x) {
    speed.x = x;
}

void BallController::setActive(bool isActive){
    active = isActive;
}

void BallController::setSpeedY(float y) {
    speed.y = y;
}

const Ball &BallController::getBall() const {
    return *ball;
}

bool BallController::isActive() const {
    return active;
}

