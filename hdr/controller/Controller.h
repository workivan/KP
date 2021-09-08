//
// Created by ivan on 12.08.2021.
//

#ifndef C___CONTROLLER_H
#define C___CONTROLLER_H


class Controller {
private:
    [[nodiscard]] virtual float x() const = 0;
    [[nodiscard]] virtual float y() const = 0;
public:
    [[nodiscard]] virtual float left() const = 0;
    [[nodiscard]] virtual float right() const = 0;
    [[nodiscard]] virtual float top() const= 0;
    [[nodiscard]] virtual float bottom() const= 0;
    virtual ~Controller() = default;
    virtual void update() = 0;
};


#endif //C___CONTROLLER_H
