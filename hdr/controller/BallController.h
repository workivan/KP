//
// Created by ivan on 12.08.2021.
//

#ifndef C___BALLCONTROLLER_H
#define C___BALLCONTROLLER_H

#include <memory>
#include "Controller.h"
#include "shape/Ball.h"


class  BallController: public Controller{
private:
    std::unique_ptr<Ball> ball;
    sf::Vector2f speed;

    bool active;
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
    explicit BallController(bool);
    void setSpeedX(float);
    void setSpeedY(float);

    [[nodiscard]] const Ball& getBall() const;
    [[nodiscard]] bool isActive() const;
    void setActive(bool active);
};


#endif //C___BALLCONTROLLER_H
