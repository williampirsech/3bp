#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dynamics.h"
#include "ScreenMovement.h"
#include "MassiveMovable.h"
#include "Util.h"

// The fixture for testing class Foo.
class DynamicsTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  DynamicsTests()
    : dynamics(movement)
  {}

  ~DynamicsTests() override {}

  void SetUp() override {}

  void TearDown() override {}

  Dynamics dynamics;
  ScreenMovement movement;
};

class MovementMock : public ScreenMovement {
    MOCK_METHOD(void, addVelocity, (Movable&, const TimeDelta, const float, const float));
    MOCK_METHOD(void, moveForward, (Movable&, const TimeDelta));
};

// If no objects then incrementing system still works
TEST_F(DynamicsTests, NoObjects) {
    dynamics.incrementSystem(1);
    ASSERT_EQ(1,1);
}

// If no mass in system then increment system makes no change.
TEST_F(DynamicsTests, NoMassNoMovment) {
    const auto pos1 = sf::Vector2f(0,0);
    const auto pos2 = sf::Vector2f(10,10);

    auto cs1 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    Movable movable1(cs1);
    movable1.getShape()->setPosition(pos1);
    auto cs2 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    Movable movable2(cs2);
    movable2.getShape()->setPosition(pos2);
   
    dynamics.add(movable1);
    dynamics.add(movable2);
    dynamics.incrementSystem(1);
   
    ASSERT_EQ(movable1.getShape()->getPosition() , pos1);
    ASSERT_EQ(movable2.getShape()->getPosition() , pos2);
}

// If one mass and one non-mass in system then incrementing system changes position of nonmass, while mass remains same position
TEST_F(DynamicsTests, MassNoMassOneMovement) {
    const auto pos1 = sf::Vector2f(9.6,5.5);
    const auto pos2 = sf::Vector2f(11.3,12.4);

    auto cs1 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    Movable movable1(cs1);
    movable1.getShape()->setPosition(pos1);
    auto cs2 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    MassiveMovable massive(cs2,1);
    massive.getShape()->setPosition(pos2);
    
    dynamics.add(movable1);
    dynamics.add(massive);
    dynamics.incrementSystem(1);

    ASSERT_NE(movable1.getShape()->getPosition(), pos1);
    ASSERT_EQ(massive.getShape()->getPosition(), pos2);
}

// IF time increment zero then no change
TEST_F(DynamicsTests, NoTimeNoChange) {
    const auto pos1 = sf::Vector2f(29.1,22.5);
    const auto pos2 = sf::Vector2f(-11.7,9.4);

    auto cs1 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    MassiveMovable massive1(cs1,1);
    massive1.getShape()->setPosition(pos1);
    auto cs2 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    MassiveMovable massive2(cs2,1);
    massive2.getShape()->setPosition(pos2);

    dynamics.add(massive1);
    dynamics.add(massive2);
    dynamics.incrementSystem(0);

    ASSERT_EQ(massive1.getShape()->getPosition() , pos1);
    ASSERT_EQ(massive2.getShape()->getPosition() , pos2);
}

// Two masses w/ no init velocity fall through line given by their respective initial positions
TEST_F(DynamicsTests, FallingTrajectory) {
    const auto pos1 = sf::Vector2f(29.1,22.5);
    const auto pos2 = sf::Vector2f(-11.7,9.4);
    const auto vec = pos2-pos1;

    auto cs1 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    MassiveMovable massive1(cs1,0.01);
    massive1.getShape()->setPosition(pos1);
    auto cs2 = std::make_shared<sf::CircleShape>(sf::CircleShape(1));
    MassiveMovable massive2(cs2,0.01);
    massive2.getShape()->setPosition(pos2);

    dynamics.add(massive1);
    dynamics.add(massive2);
    dynamics.incrementSystem(0.1);

    const auto newpos1 = massive1.getShape()->getPosition();
    const auto newpos2 = massive2.getShape()->getPosition();
    const auto newvec = newpos2-newpos1;

    EXPECT_NE(vec, newvec); // check that the system actually changed
    ASSERT_NEAR(newvec.x/vec.x, newvec.y/vec.y,0.00001);
}