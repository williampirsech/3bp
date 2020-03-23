#pragma once

#include "Util.h"
#include "Movable.h"
#include "SFML/graphics.hpp"

// Handles movement in relation to a window and a time delta

class ScreenMovement {
    public:

    virtual ~ScreenMovement() {}
    
    //explicit ScreenMovement(const sf::Window&);

    virtual const Coordinate getPosition(const Movable&) const noexcept;
    
    virtual void setPosition(Movable&, const float, const float) const noexcept;
    //virtual void setRelativePosition(Movable&, const float, const float) const noexcept;
    //virtual void setRelativeSize(Movable&, const float, const float) const noexcept;
    virtual void setRotation(Movable&,const Angle) const noexcept;
    virtual void setVelocity(Movable&, const double, const double) const noexcept;
    virtual void rotate(Movable&, const TimeDelta, const Angle) const noexcept;
    virtual void moveForward(Movable&, const TimeDelta) const noexcept;
    virtual void addVelocity(Movable&, const TimeDelta, const float, const float) const noexcept;
    virtual void accelerate(Movable&, const TimeDelta, const float) const noexcept;

    private:
    //const sf::Window& window;
};