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
      v1 = planetMaker(10,7,sf::Color::White);
      v2 = planetMaker(10,11,sf::Color::White);

      v1 = sf::VertexArray(sf::TriangleFan);
      v1.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
      v1.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
      v1.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
      v1.append(sf::Vertex(sf::Vector2f(1.f,1.f)));

      v2 = sf::VertexArray(sf::TriangleFan);
      v2.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
      v2.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
      v2.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
      v2.append(sf::Vertex(sf::Vector2f(1.f,1.f)));
  }

  ~CollisionTests() override {}

  void SetUp() override {}

  void TearDown() override {}

  sf::VertexArray v1,v2;
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
    ASSERT_TRUE(Collision::collidesWith(m1,m2) | Collision::collidesWith(m2,m1));
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

TEST_F(CollisionTests, SquareTriangleTest) {
    v1 = sf::VertexArray(sf::TriangleFan);
    v1.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
    v1.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
    v1.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
    v1.append(sf::Vertex(sf::Vector2f(1.f,1.f)));

    v2 = sf::VertexArray(sf::TriangleFan);
    v2.append(sf::Vertex(sf::Vector2f(-1.f,0.f)));
    v2.append(sf::Vertex(sf::Vector2f(0,-2.f)));
    v2.append(sf::Vertex(sf::Vector2f(0,2.f)));
    
    Movable m1(v1), m2(v2);
    m1.setPosition(0,0);
    m2.setPosition(10,0);

    ASSERT_FALSE(Collision::collidesWith(m1,m2) & Collision::collidesWith(m2,m1));
}