//
// Created by ikuzin on 06.06.2021.
//

#include <controller/BlockController.h>
#include "core/Logic.h"


sf::Vector2f const Logic::BALL_DEFAULT_POSITION = sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
sf::Vector2f const Logic::PLATFORM_DEFAULT_POSITION = sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT * 0.85);

Logic::Logic() :
        platformCtrl(std::make_unique<PlatformController>()),
        ballCtrl(std::make_unique<BallController>(true),
                 std::make_unique<BallController>(false)) {
    for (int iX{0}; iX < ROW_LENGTH - 2; iX++) {
        for (int iY{0}; iY < COLUMN_LENGTH; iY++) {
            auto shape = sf::Vector2f(
                    (iX + 1) * (BLOCK_WIDTH + 3) + 22,
                    (iY + 2) * (BLOCK_HEIGHT + 3)
            );
            blockCtrls.emplace_back(std::make_unique<BlockController>(shape));
        }
    }
}

template<class T1, class T2>
bool Logic::isIntersecting(T1 &mA, T2 &mB) {
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}


std::pair<bool, bool> Logic::testCollision(const Controller &TCtrl, const Controller &ballCtrl) {
    float overlapLeft{ballCtrl.right() - TCtrl.left()};
    float overlapRight{TCtrl.right() - ballCtrl.left()};
    float overlapTop{ballCtrl.bottom() - TCtrl.top()};
    float overlapBottom{TCtrl.bottom() - ballCtrl.top()};

    bool ballFromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool ballFromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    return std::abs(minOverlapX) < std::abs(minOverlapY) ? std::pair(true, ballFromLeft) : std::pair(false,
                                                                                                     ballFromTop);
}


void Logic::update() {
    platformCtrl->update();
    ballCtrl.first->update();
    ballCtrl.second->update();
    for (auto &bonus: bonusCtrls)
        bonus->update();

    const auto& specblock = blockCtrls.back();
    specblock->update();

    ballUpdate(*ballCtrl.first, *platformCtrl);
    blocksUpdate(blockCtrls, *ballCtrl.first);

    if (ballCtrl.second->isActive()) {
        ballUpdate(*ballCtrl.second, *platformCtrl);
        blocksUpdate(blockCtrls, *ballCtrl.second);
    }

    bonusesUpdate(bonusCtrls, *platformCtrl);
}


const PlatformController &Logic::getPlatformCtrl() const {
    return *platformCtrl;
}

const LogicSupport::Matrix &Logic::getBlockCtrls() const {
    return blockCtrls;
}

const BallController &Logic::getBallCtrls(int i) const {
    return i == 0 ? *ballCtrl.first : *ballCtrl.second;
}

void Logic::launchBonus(BlockControllerSupport::HiredType &type, const sf::Vector2f &pos) {
    if (type == BlockControllerSupport::NONE)
        return;
    bonusCtrls.push_back(std::make_unique<BonusController>(pos, BONUS_SPEED, type));
}

const LogicSupport::Bonuses &Logic::getBonusCtrls() const {
    return bonusCtrls;
}

void Logic::ballUpdate(BallController &ball, PlatformController &platform) {
    if (isIntersecting(platform, ball)) {
        std::pair<bool, bool> result = testCollision(platform, ball);
        float bspeed = Logic::BALL_SPEED;
        if (result.first) {
            ball.setSpeedX((bool) result.second ? -bspeed : bspeed);
        } else {
            ball.setSpeedY((bool) result.second ? -bspeed : bspeed);
        }
    }
}

void Logic::blocksUpdate(LogicSupport::Matrix &blocks, BallController &ball) {
    for (auto &block: blocks) {
        if (isIntersecting(*block, ball)) {
            std::pair<bool, bool> result = testCollision(*block, ball);
            auto bonusType = block->setDestroy(true);
            launchBonus(bonusType, block->getBlockPosition());
            float bspeed = Logic::BALL_SPEED;
            if (result.first) {
                ball.setSpeedX((bool) result.second ? -bspeed : bspeed);
            } else {
                ball.setSpeedY((bool) result.second ? -bspeed : bspeed);
            }
            break;
        }
    }

    blocks.erase(
            std::remove_if(
                    blocks.begin(),
                    blocks.end(),
                    [](const std::unique_ptr<BlockController> &blockCtrl) {
                        return blockCtrl->isDestroy();
                    }
            ), blocks.end()
    );
}

void Logic::addSpecialBlock() {
    const sf::Vector2f pos{Logic::BALL_DEFAULT_POSITION.x, Logic::BALL_DEFAULT_POSITION.y - 50};
    const sf::Vector2f size{90.f, 10.f};
    const sf::Vector2f speed{Logic::PLATFORM_SPEED, 0};
    sf::Color color = sf::Color::Green;
    auto type = BlockControllerSupport::BlockType::HEALTHED;
    unsigned int health = 3;
    blockCtrls.push_back(std::make_unique<BlockController>(pos, size, color, health, speed, type));
}

void Logic::bonusesUpdate(LogicSupport::Bonuses & bonuses, PlatformController & platform) {
    for (auto &bonus: bonuses) {
        if (isIntersecting(platform, *bonus)) {
            bonus->setExpired(true);
            switch (bonus->getType()) {
                case BlockControllerSupport::HiredType::NEWBLOCK:
                    addSpecialBlock();
                    break;
                case BlockControllerSupport::HiredType::SECONDBALL:
                    ballCtrl.second->setActive(true);
                    break;
                default: {}
            }
        }
    }

    bonuses.erase(std::remove_if(
                             bonuses.begin(),
                             bonuses.end(),
                             [](const std::unique_ptr<BonusController> &bonusCtrl) {
                                 return bonusCtrl->isExpired();
                             }
                     ), bonuses.end()
    );
}
