#pragma once

#include "Util.h"
#include "Movable.h"
#include "SFML/graphics.hpp"

// Handles movement in relation to a window and a time delta

class ScreenMovement {
    public:

    explicit ScreenMovement(const sf::Window&);

    const Coordinate getPosition(const Movable&) const noexcept;
    
    void setPosition(Movable&, const float, const float) const noexcept;
    void setRotation(Movable&,const Angle) const noexcept;
    void setVelocity(Movable&, const double, const double) const noexcept;
    void rotate(Movable&, const TimeDelta, const Angle) const noexcept;
    void moveForward(Movable&, const TimeDelta) const noexcept;
    void addVelocity(Movable&, const TimeDelta, const float, const float) const noexcept;
    void accelerate(Movable&, const TimeDelta, const float) const noexcept;

    private:
    const sf::Window& window;
};