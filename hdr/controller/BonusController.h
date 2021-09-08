//
// Created by ivan on 30.08.2021.
//

#ifndef C___BONUSCONTROLLER_H
#define C___BONUSCONTROLLER_H


#include <memory>
#include <shape/Bonus.h>
#include "BlockController.h"

class BonusController : public Controller {
private:
    std::unique_ptr<Bonus> bonus;

    BlockControllerSupport::HiredType type;
    sf::Vector2f speed{};
    bool expired{false};
private:
    [[nodiscard]] float x() const override;
    [[nodiscard]] float y() const override;

public:
    void update() override;
    [[nodiscard]] float left() const override;
    [[nodiscard]] float right() const override;
    [[nodiscard]] float top() const override;
    [[nodiscard]] float bottom() const override;

public:
    explicit BonusController(const sf::Vector2f &, float, BlockControllerSupport::HiredType &);

    [[nodiscard]] const Bonus &getBonus() const;
    [[nodiscard]] BlockControllerSupport::HiredType getType() const;
    [[nodiscard]] bool isExpired() const;

    void setExpired(bool expired);
};


#endif //C___BONUSCONTROLLER_H
