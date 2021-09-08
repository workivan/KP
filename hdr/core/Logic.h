//
// Created by ikuzin on 06.06.2021.
//

#ifndef KP_LOGIC_H
#define KP_LOGIC_H

#include <controller/BallController.h>
#include <controller/PlatformController.h>
#include <controller/BlockController.h>
#include <controller/BonusController.h>

#include "memory"
#include "vector"

#include "shape/Platform.h"
#include "shape/Ball.h"
#include "shape/Block.h"

namespace LogicSupport {
    using Matrix = std::vector<std::unique_ptr<BlockController>>;
    using Balls = std::pair<std::unique_ptr<BallController>, std::unique_ptr<BallController>>;
    using Bonuses = std::vector<std::unique_ptr<BonusController>>;
}


class Logic {
public:
    static const unsigned int WINDOW_WIDTH = 800;
    static const unsigned int WINDOW_HEIGHT = 600;

    constexpr static const float PLATFORM_HEIGHT = 10.f;
    constexpr static const float PLATFORM_WIDTH = 80.f;
    constexpr static const float PLATFORM_SPEED = 8.f;

    constexpr static const float BALL_RADIUS = 5;

    constexpr static const float BONUS_HEIGHT = 20.f;
    constexpr static const float BONUS_WIDTH = 20.f;
    constexpr static const float BONUS_SPEED = 2.f;

    static sf::Vector2f const BALL_DEFAULT_POSITION;
    static sf::Vector2f const PLATFORM_DEFAULT_POSITION;

    static const unsigned int ROW_LENGTH = 10; //будет 8 в итоге потому что минус 2 по краям
    static const unsigned int COLUMN_LENGTH = 4;

    static const unsigned int BLOCK_WIDTH = WINDOW_WIDTH / ROW_LENGTH ;
    static const unsigned int BLOCK_HEIGHT = 17.f;
private:
    std::unique_ptr<PlatformController> platformCtrl;
    LogicSupport::Matrix blockCtrls;
    LogicSupport::Balls ballCtrl;
    LogicSupport::Bonuses bonusCtrls;

    inline static float BALL_SPEED = 4.f;
private:
    template <class T1, class T2>bool isIntersecting(T1& mA, T2& mB);
    void launchBonus(BlockControllerSupport::HiredType &, const sf::Vector2f&);

    void ballUpdate(BallController&, PlatformController&);
    void blocksUpdate(LogicSupport::Matrix&, BallController&);
    void bonusesUpdate(LogicSupport::Bonuses&, PlatformController&);
    void addSpecialBlock();
public:
    explicit Logic();

public:
    static float getBallSpeed() { return BALL_SPEED;};
    static void updateBallSpeed() { BALL_SPEED +=.4f;};

    void update();
    [[nodiscard]] const PlatformController& getPlatformCtrl() const ;
    [[nodiscard]] const LogicSupport::Matrix& getBlockCtrls() const;
    [[nodiscard]] const BallController& getBallCtrls(int) const;
    [[nodiscard]] const LogicSupport::Bonuses &getBonusCtrls() const;
    static std::pair<bool, bool> testCollision(const Controller &,  const Controller &);
};


#endif //KP_LOGIC_H
