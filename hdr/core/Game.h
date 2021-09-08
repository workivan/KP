//
// Created by ikuzin on 06.06.2021.
//

#ifndef KP_GAME_H
#define KP_GAME_H


#include <memory>

#include "core/Window.h"

class Game {
private:
    std::unique_ptr<Window> app;
public:
    Game() : app(std::make_unique<Window>()) {};
    void run();
};


#endif //KP_GAME_H
