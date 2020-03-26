#pragma once

#include "SFML/graphics.hpp"
#include "Util.h"
#include "Movable.h"

class Collision {
    public:
    static bool collidesWith_rad(const Movable&, const Movable&);
    static bool collidesWith_vertexSep(const Movable&, const Movable&);
};