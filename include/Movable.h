#pragma once

#include "Util.h"
#include "SFML/graphics.hpp"

enum class CollidableState {Transparent, Rigid};

class Movable  {
    
    public: 

    explicit Movable(sf::VertexArray& vert);

    void setRotation(const Angle) noexcept;
    void setPosition(const float, const float) noexcept;
    void setPosition(const sf::Vector2f&) noexcept;
    void setVelocity(const float, const float) noexcept;
    void setMass(const Mass) noexcept;
    
    void rotate(const TimeDelta, const Angle) noexcept;
    void moveForward(const TimeDelta) noexcept;
    void addVelocity(const TimeDelta, const float, const float) noexcept;
    void accelerate(const TimeDelta, const float) noexcept;
    
    const Coordinate getPosition() const noexcept;
    const Angle getRotation() const noexcept;
    const sf::VertexArray& getVertexArray() const noexcept;
    const Mass getMass() const noexcept;

    CollidableState collidableState;

    protected:
    sf::VertexArray& vert;

    private:
    Velocity velocity;
    sf::Vector2f center;
    sf::Transform transform;
    Angle angle;
    Mass mass;

    void _rotationUpdate() noexcept;
    float _radius2;

    friend class Dynamics;
    friend class Collision;
};