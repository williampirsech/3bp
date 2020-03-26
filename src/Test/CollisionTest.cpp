#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dynamics.h"
#include "Collision.h"
#include "Movable.h"
#include "Util.h"

// The fixture for testing class Foo.
class CollisionTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  CollisionTests()
  {
      v1 = planetMaker(10,4,sf::Color::White);
      v2 = planetMaker(10,4,sf::Color::White);

        sqV.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
        sqV.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
        sqV.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
        sqV.append(sf::Vertex(sf::Vector2f(1.f,1.f)));
        
        triV.append(sf::Vertex(sf::Vector2f(-1.f,0.f)));
        triV.append(sf::Vertex(sf::Vector2f(0,-2.f)));
        triV.append(sf::Vertex(sf::Vector2f(0,2.f)));
    
  }

  ~CollisionTests() override {}

  void SetUp() override {}

  void TearDown() override {}

  sf::VertexArray v1,v2, sqV, triV;
};

// Simple Noncollision
TEST_F(CollisionTests, NonCollisionSimple) {
    Movable m1(v1), m2(v2);
    m1.setPosition(0,0);
    m2.setPosition(100,100);
    ASSERT_FALSE(Collision::collidesWith(m1,m2));
    ASSERT_FALSE(Collision::collidesWith(m2,m1));
}

// Simple collision
TEST_F(CollisionTests, CollisionSimple) {
    Movable m1(v1), m2(v2);
    m1.setPosition(0,0);
    m2.setPosition(1,0);
    ASSERT_TRUE(Collision::collidesWith(m1,m2));
    ASSERT_TRUE(Collision::collidesWith(m2,m1));
}

// Simple noncollision, except rotated
TEST_F(CollisionTests, NonCollisionSimpleRotated) {
    Movable m1(v1), m2(v2);
    m1.setPosition(0,0);
    m2.setPosition(100,100);
    m1.rotate(1,-44);
    m2.rotate(1,66);
    ASSERT_FALSE(Collision::collidesWith(m1,m2));
    ASSERT_FALSE(Collision::collidesWith(m2,m1));
}

TEST_F(CollisionTests, NonCollisionPlanets) {
    auto c1 = planetMaker(40.f,80,sf::Color::White);
    auto c2 = planetMaker(5.f,80,sf::Color::White);
    Movable m1(c1), m2(c2);
    m1.setPosition(100,100);
    m2.setPosition(50,50);
    ASSERT_FALSE(Collision::collidesWith(m1,m2));
    ASSERT_FALSE(Collision::collidesWith(m2,m1));
}

// Noncollision between square and distant triangle pointing to square
TEST_F(CollisionTests, NonCollisionSquareTriangle) {
    auto triV = sf::VertexArray(sf::TriangleFan);
    
    Movable m1(triV), m2(sqV);
    m1.setPosition(0,0);
    m2.setPosition(10,0);

    ASSERT_FALSE(Collision::collidesWith(m1,m2));
    ASSERT_FALSE(Collision::collidesWith(m2,m1));
}

// Collision with square and triangle whose point is inside square
TEST_F(CollisionTests, CollisionSquareTriangle) {
    auto triV = sf::VertexArray(sf::TriangleFan);
    
    Movable m1(triV), m2(sqV);
    m1.setPosition(0,0);
    m2.setPosition(2.2f,0);

    ASSERT_TRUE(Collision::collidesWith(m1,m2));
    ASSERT_TRUE(Collision::collidesWith(m2,m1));
}

// Collision with square and triangle whose point is inside square but triangle's construction is clockwise instead of counterclockwise.
TEST_F(CollisionTests, DISABLED_CollisionInverted) {
    auto triV2 = sf::VertexArray(sf::TriangleFan);
    triV2.append(sf::Vertex(sf::Vector2f(-1.f,0.f)));
    triV2.append(sf::Vertex(sf::Vector2f(0,2.f)));
    triV2.append(sf::Vertex(sf::Vector2f(0,-2.f)));
    Movable m1(triV2), m2(sqV);
    m1.setPosition(0,0);
    m2.setPosition(2.2f,0);

    ASSERT_TRUE(Collision::collidesWith(m1,m2));
    ASSERT_TRUE(Collision::collidesWith(m2,m1));
}

// Nonollision radius test: two objects far apart
TEST_F(CollisionTests, RadiusNonCollision) {
    auto p1 = planetMaker(10,8, sf::Color::White);
    auto p2 = planetMaker(10,8, sf::Color::White);

    Movable m1(p1), m2(p2);
    m1.setPosition(0,0); m2.setPosition(30,0);
    ASSERT_FALSE(Collision::collidesWith_rad(m1,m2));
}

// Collision radius test
TEST_F(CollisionTests, RadiusCollision) {
    auto p1 = planetMaker(10,8, sf::Color::White);
    auto p2 = planetMaker(10,8, sf::Color::White);

    Movable m1(p1), m2(p2);
    m1.setPosition(0,0); m2.setPosition(8,0);
    ASSERT_TRUE(Collision::collidesWith_rad(m1,m2));
}