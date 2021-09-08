#include <iostream>
#include <memory>

#include "core/Game.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto game = std::make_unique<Game>();
    game->run();
    return 0;
}
