//
// Created by ivan on 13.08.2021.
//

#ifndef C___BLOCKCONTROLLER_H
#define C___BLOCKCONTROLLER_H

#include <vector>
#include <memory>

#include "Controller.h"
#include <shape/Block.h>

namespace BlockControllerSupport {
    enum HiredType {
        NONE,
        SECONDBALL,
        NEWBLOCK
    };

    enum BlockType {
        UNDELETED,
        HIRED_BONUS,
        HEALTHED,
        SPEEDUP
    };
}


class BlockController : public Controller {
private:
    [[nodiscard]] float x() const override;
    [[nodiscard]] float y() const override;
    void setSpeedX(float);

private:
    std::unique_ptr<Block> block;
    bool destroy{false};
    bool special{false};
    BlockControllerSupport::BlockType type;
    unsigned int health{2};
    sf::Vector2f speed;

public:
    [[nodiscard]] bool isDestroy() const;
    BlockControllerSupport::HiredType setDestroy(bool destroy);

public:
    void update() override;
    [[nodiscard]] float left() const override;
    [[nodiscard]] float right() const override;
    [[nodiscard]] float top() const override;
    [[nodiscard]] float bottom() const override;

public:
    explicit BlockController(const sf::Vector2f &);
    BlockController(const sf::Vector2f&,
                    const sf::Vector2f&,
                    sf::Color,
                    unsigned int,
                    const sf::Vector2f&,
                    BlockControllerSupport::BlockType);
    [[nodiscard]] const Block &getBlock() const;
    [[nodiscard]] const sf::Vector2f &getBlockPosition() const;
};


#endif //C___BLOCKCONTROLLER_H
