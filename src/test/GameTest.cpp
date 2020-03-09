#include "gtest/gtest.h"
#include "Game.h"

// Game initializes, sets player position to (10,10) => player pos equal to (10,10) 
TEST(GameTest, InitTest) {
    Game g;
    g.init();
    g.setPlayerPosition(10,10);
    auto pp = g.getPlayerPosition();
    ASSERT_EQ(pp.x, 10);
    ASSERT_EQ(pp.y, 10);
}