//
// Created by ivan on 13.08.2021.
//

#ifndef C___PLATFORMCONTROLLER_H
#define C___PLATFORMCONTROLLER_H

#include <memory>
#include "Controller.h"
#include "shape/Platform.h"

class PlatformController : public Controller {
private:
    std::unique_ptr<Platform> platform;
    sf::Vector2f speed;
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
    explicit PlatformController();
    void setSpeedX(float);

    [[nodiscard]] const Platform & getPlatform() const {return *platform;}
};


#endif //C___PLATFORMCONTROLLER_H
