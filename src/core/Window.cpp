//
// Created by ikuzin on 06.06.2021.
//

#include <core/Window.h>


void Window::render() {
    screen.clear();
    screen.draw(*this);
    screen.display();
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    const auto &platformCtrl = state->getPlatformCtrl();
    target.draw(platformCtrl.getPlatform(), states);

    const auto &ballCtrlFirst = state->getBallCtrls(0);
    target.draw(ballCtrlFirst.getBall(), states);

    const auto& ballCtrlSec = state->getBallCtrls(1);
    if(ballCtrlSec.isActive())
        target.draw(ballCtrlSec.getBall(), states);

    for (const auto &bonusCtrl: state->getBonusCtrls()) {
        target.draw(bonusCtrl->getBonus(), states);
    }

    for (const auto &block: state->getBlockCtrls()) {
        target.draw(block->getBlock(), states);
    }
}

void Window::stateUpdate() {
    state->update();
}


