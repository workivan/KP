//
// Created by ivan on 30.08.2021.
//

#ifndef C___BONUS_H
#define C___BONUS_H

#include "SFML/Graphics.hpp"

class Bonus: public sf::RectangleShape{
public:
    explicit Bonus(const sf::Vector2f&, const sf::Vector2f&);
};


#endif //C___BONUS_H
