#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>

// Should probably wrap in a namespace Util::

using Coordinate = sf::Vector2f;
using Angle = float;
using Velocity = sf::Vector2f;

// should have a constexpr cos, sin table to draw from

constexpr double PI() { return acos(-1); }
constexpr double PI2() { return 2*PI(); }
constexpr double R2D() { return 180/PI(); }
constexpr double D2R() { return PI()/180; }

// Probably wrong
inline Angle normalizeAngle(const Angle theta) noexcept {
    Angle theta0 = fmod(theta,PI2());
    if (theta0 < 0) theta0 += PI2();
    return theta0;
}