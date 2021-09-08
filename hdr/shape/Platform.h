//
// Created by ikuzin on 06.06.2021.
//

#ifndef KP_PLATFORM_H
#define KP_PLATFORM_H

#include "SFML/Graphics.hpp"


class Platform : public sf::RectangleShape {
public:
    explicit Platform(const sf::Vector2f& shape);
};


#endif //KP_PLATFORM_H
