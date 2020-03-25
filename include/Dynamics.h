#pragma once

#include "Util.h"
#include "Movable.h"
#include "Collision.h"

class Dynamics {
    public:
    Dynamics() {}
    //explicit Dynamics(const ScreenMovement&);
    std::vector<Movable*> getMovables() const noexcept;
    void add(Movable&);
    void incrementSystem(const TimeDelta) const noexcept;
    void collisionDetect() const noexcept;
    private:
    mutable sf::Vector2f _res;
    std::vector<Movable*> movables;
};