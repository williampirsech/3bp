#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <fstream>
#include <sstream>

using std::min;
using std::max;

// Should probably wrap in a namespace Util::

using Coordinate = sf::Vector2f;
using Angle = float;
using Velocity = sf::Vector2f;
using TimeDelta = float;
using Mass = float;

constexpr double PI() { return acos(-1); }
constexpr double PI2() { return 2*PI(); }
constexpr double R2D() { return 180/PI(); }
constexpr double D2R() { return PI()/180; }

inline float norm(const sf::Vector2f vec) {
    return sqrt(vec.x*vec.x+vec.y*vec.y);
}

inline float norm2(const sf::Vector2f vec) {
    return (vec.x*vec.x+vec.y*vec.y);
}

inline float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}
