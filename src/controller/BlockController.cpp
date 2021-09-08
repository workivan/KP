//
// Created by ivan on 13.08.2021.
//
#include <core/Logic.h>
#include "controller/BlockController.h"

float BlockController::x() const {
    return block->getPosition().x;
}

float BlockController::y() const {
    return block->getPosition().y;
}

float BlockController::left() const {
    return x() - block->getSize().x / 2.f;
}

float BlockController::right() const {
    return x() + block->getSize().x / 2.f;
}

float BlockController::top() const {
    return y() - block->getSize().y / 2.f;
}

float BlockController::bottom() const {
    return y() + block->getSize().y / 2.f;
}

BlockController::BlockController(const sf::Vector2f &shape) {
    std::vector<BlockControllerSupport::BlockType> blockTypes = {
            BlockControllerSupport::BlockType::UNDELETED,
            BlockControllerSupport::BlockType::HIRED_BONUS,
            BlockControllerSupport::BlockType::HEALTHED,
            BlockControllerSupport::BlockType::SPEEDUP
    };
    block = std::make_unique<Block>(shape);
    type = blockTypes[rand() % blockTypes.size()];
}

const Block &BlockController::getBlock() const {
    return *block;
}

void BlockController::update() {
    if (special) {
        block->move(speed);
        if (left() <= 0 || right() >= Logic::WINDOW_WIDTH) {
            setSpeedX(-speed.x);
        }
    }
}

bool BlockController::isDestroy() const { return destroy; }

BlockControllerSupport::HiredType BlockController::setDestroy(bool destroy) {
    std::vector<BlockControllerSupport::HiredType> hiredTypes = {
            BlockControllerSupport::HiredType::NEWBLOCK,
            BlockControllerSupport::HiredType::SECONDBALL,
            BlockControllerSupport::HiredType::NONE
    };
    switch (type) {
        case BlockControllerSupport::BlockType::HIRED_BONUS:
            BlockController::destroy = destroy;
            return hiredTypes[rand() % hiredTypes.size()];
        case BlockControllerSupport::BlockType::HEALTHED:
            if (--health < 1)
                BlockController::destroy = destroy;
            return BlockControllerSupport::HiredType::NONE;
        case BlockControllerSupport::BlockType::SPEEDUP: {
            BlockController::destroy = destroy;
            Logic::updateBallSpeed();
            return BlockControllerSupport::HiredType::NONE;
        }
        case BlockControllerSupport::BlockType::UNDELETED:
            return BlockControllerSupport::HiredType::NONE;
    }
}

const sf::Vector2f &BlockController::getBlockPosition() const {
    return block->getPosition();
}

BlockController::BlockController(const sf::Vector2f &pos, const sf::Vector2f &size, sf::Color color,
                                 unsigned int health, const sf::Vector2f& speed,
                                 BlockControllerSupport::BlockType type) {
    block = std::make_unique<Block>(pos, size, color);
    this->type = type;
    this->health = health;
    this->speed = speed;
    special = true;
}

void BlockController::setSpeedX(float x) {
    speed.x = x;
}
