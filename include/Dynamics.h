#pragma once

#include "Util.h"
#include "Movable.h"
#include "MassiveMovable.h"
#include "ScreenMovement.h"

class Dynamics {
    public:
    explicit Dynamics(const ScreenMovement&);
    std::vector<Movable*> getMovables() const noexcept;
    void add(Movable&);
    void add(MassiveMovable&);
    void incrementSystem(const TimeDelta) const noexcept;
    private:
    mutable sf::Vector2f _res;
    std::vector<Movable*> movables;
    std::vector<MassiveMovable*> massives;
    const ScreenMovement& movement;
};