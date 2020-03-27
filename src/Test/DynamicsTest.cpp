#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dynamics.h"
#include "Util.h"
#include "MovableCreator.h"

// The fixture for testing class Foo.
class DynamicsTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  DynamicsTests()
  {
  }

  ~DynamicsTests() override {}

  void SetUp() override {}

  void TearDown() override {}

  Dynamics dynamics;
  sf::VertexArray v1,v2;
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

    
    Movable movable1(v1);
    movable1.setPosition(pos1.x,pos1.y);
    Movable movable2(v2);
    movable2.setPosition(pos2.x,pos2.y);

    dynamics.add(movable1);
    dynamics.add(movable2);
    dynamics.incrementSystem(1);
   
    ASSERT_EQ(movable1.getPosition() , pos1);
    ASSERT_EQ(movable2.getPosition() , pos2);
}

// If one mass and one non-mass in system then incrementing system changes position of nonmass, while mass remains same position
TEST_F(DynamicsTests, MassNoMassOneMovement) {
    const auto pos1 = sf::Vector2f(9.6,5.5);
    const auto pos2 = sf::Vector2f(11.3,12.4);

    Movable movable1 = MovableCreator::planetMaker(10,20,sf::Color::White);
    movable1.setPosition(pos1.x,pos2.y);
    Movable massive = MovableCreator::planetMaker(10,20,sf::Color::White);
    massive.setMass(1);
    massive.setPosition(pos2);
    
    dynamics.add(movable1);
    dynamics.add(massive);
    dynamics.incrementSystem(1);

    ASSERT_NE(movable1.getPosition(), pos1);
    ASSERT_EQ(massive.getPosition(), pos2);
}

// IF time increment zero then no change
TEST_F(DynamicsTests, NoTimeNoChange) {
    const auto pos1 = sf::Vector2f(29.1,22.5);
    const auto pos2 = sf::Vector2f(-11.7,9.4);

    Movable massive1(v1);
    massive1.setMass(1);
    massive1.setPosition(pos1);
    Movable massive2(v2);
    massive2.setMass(1);
    massive2.setPosition(pos2);

    dynamics.add(massive1);
    dynamics.add(massive2);
    dynamics.incrementSystem(0);

    ASSERT_EQ(massive1.getPosition() , pos1);
    ASSERT_EQ(massive2.getPosition() , pos2);
}

// Two masses w/ no init velocity fall through line given by their respective initial positions
TEST_F(DynamicsTests, FallingTrajectory) {
    const auto pos1 = sf::Vector2f(29.1,22.5);
    const auto pos2 = sf::Vector2f(-11.7,9.4);
    const auto vec = pos2-pos1;

    Movable massive1(v1);
    massive1.setMass(0.01);
    massive1.setPosition(pos1);
    Movable massive2(v2);
    massive2.setMass(0.01);
    massive2.setPosition(pos2);

    dynamics.add(massive1);
    dynamics.add(massive2);
    dynamics.incrementSystem(0.1);

    const auto newpos1 = massive1.getPosition();
    const auto newpos2 = massive2.getPosition();
    const auto newvec = newpos2-newpos1;

    EXPECT_NE(vec, newvec); // check that the system actually changed
    ASSERT_NEAR(newvec.x/vec.x, newvec.y/vec.y,0.00001);
}