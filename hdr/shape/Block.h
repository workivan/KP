//
// Created by ivan on 11.08.2021.
//


#ifndef C___BLOCK_H
#define C___BLOCK_H

#include "SFML/Graphics.hpp"

class Block : public sf::RectangleShape {
public:
    explicit Block(const sf::Vector2f& shape);
    Block(const sf::Vector2f& , const sf::Vector2f&, sf::Color );
};


#endif //C___BLOCK_H
