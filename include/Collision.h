#pragma once

#include "SFML/graphics.hpp"
#include "Util.h"
#include "Movable.h"

class Collision {
    public:
    static bool collidesWith_rad(const Movable&, const Movable&);
    static bool collidesWith(const Movable&, const Movable&);
};