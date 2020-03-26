#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dynamics.h"
#include "Collision.h"
#include "Movable.h"
#include "Util.h"

// The fixture for testing class Foo.
class CollisionTests : public ::testing::Test {
 protected:

  CollisionTests()
  {    
  }

  ~CollisionTests() override {}

  void SetUp() override {}

  void TearDown() override {}

};


/*
None of edges in triangle m2 forms separating line with square - should return true
-------
|      |
|      | <|
|      |
-------
*/
TEST_F(CollisionTests, BigSquareSmallTriangle) {
    sf::VertexArray sq(sf::TriangleFan);
    sq.append(sf::Vertex(sf::Vector2f(1000.f,-10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(-1000.f,-10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(-1000.f,10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(1000.f,10000.f)));
    sf::VertexArray tri(sf::TriangleFan);
    tri.append(sf::Vertex(sf::Vector2f(-1,0)));
    tri.append(sf::Vertex(sf::Vector2f(1,1)));
    tri.append(sf::Vertex(sf::Vector2f(1,-1)));
    Movable m1(sq),m2(tri);
    m1.setPosition(0,0);
    m2.setPosition(1003.f,0);
    ASSERT_TRUE(Collision::collidesWith_vertexSep(m1,m2));
    //m2.rotate(1,-1);
    //ASSERT_FALSE(Collision::collidesWith(m1,m2));

}

/*
One of the edges in triangle forms clear separating line - should return false
-------
|      |
|      |
|      |
|      | |> <--- rotate the triangle 180 degrees
|      |
-------
*/
TEST_F(CollisionTests, BigSquareSmallTriangleRotated) {
    sf::VertexArray sq(sf::TriangleFan);
    sq.append(sf::Vertex(sf::Vector2f(1000.f,-10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(-1000.f,-10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(-1000.f,10000.f)));
    sq.append(sf::Vertex(sf::Vector2f(1000.f,10000.f)));
    sf::VertexArray tri(sf::TriangleFan);
    tri.append(sf::Vertex(sf::Vector2f(-1,0)));
    tri.append(sf::Vertex(sf::Vector2f(1,1)));
    tri.append(sf::Vertex(sf::Vector2f(1,-1)));
    Movable m1(sq),m2(tri);
    m1.setPosition(0,0);
    m2.setPosition(1003.f,0);
    m2.rotate(1,-180);
    ASSERT_FALSE(Collision::collidesWith_vertexSep(m1,m2));
    //ASSERT_FALSE(Collision::collidesWith(m1,m2));

}

TEST_F(CollisionTests, NonCollisionPlanets) {
    auto c1 = planetMaker(40.f,80,sf::Color::White);
    auto c2 = planetMaker(5.f,80,sf::Color::White);
    Movable m1(c1), m2(c2);
    m1.setPosition(100,100);
    m2.setPosition(50,50);
    ASSERT_FALSE(Collision::collidesWith_vertexSep(m1,m2));
    ASSERT_FALSE(Collision::collidesWith_vertexSep(m2,m1));
}

// Noncollision between square and distant triangle pointing to square
TEST_F(CollisionTests, NonCollisionSquareTriangle) {
    auto triV = sf::VertexArray(sf::TriangleFan);
    triV.append(sf::Vertex(sf::Vector2f(-1.f,0.f)));
    triV.append(sf::Vertex(sf::Vector2f(0,2.f)));
    triV.append(sf::Vertex(sf::Vector2f(0,-2.f)));
    
    sf::VertexArray sqV;
    sqV.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(1.f,1.f)));
    
    Movable m1(triV), m2(sqV);
    m1.setPosition(0,0);
    m2.setPosition(10,0);

    ASSERT_FALSE(Collision::collidesWith_vertexSep(m1,m2));
    ASSERT_FALSE(Collision::collidesWith_vertexSep(m2,m1));
}

// Collision with square and triangle whose point is inside square
TEST_F(CollisionTests, CollisionSquareTriangle) {
    auto triV = sf::VertexArray(sf::TriangleFan);
    triV.append(sf::Vertex(sf::Vector2f(-1.f,0.f)));
    triV.append(sf::Vertex(sf::Vector2f(1,1.f)));
    triV.append(sf::Vertex(sf::Vector2f(1,-1.f)));
    
    sf::VertexArray sqV;
    sqV.append(sf::Vertex(sf::Vector2f(1.f,-1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(-1.f,-1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(-1.f,1.f)));
    sqV.append(sf::Vertex(sf::Vector2f(1.f,1.f)));
    Movable m1(sqV), m2(triV);
    m1.setPosition(0,0);
    m2.setPosition(1.f,0);

    ASSERT_TRUE(Collision::collidesWith_vertexSep(m1,m2) | Collision::collidesWith_vertexSep(m2,m1));
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