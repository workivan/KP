//
// Created by ivan on 11.08.2021.
//

#ifndef C___BALL_H
#define C___BALL_H

#include "SFML/Graphics.hpp"

class Ball : public sf::CircleShape {
public:
    explicit Ball(float radius);
};


#endif //C___BALL_H
