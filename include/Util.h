#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

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

inline sf::VertexArray planetMaker(float radius, int nVert, const sf::Color& color) {
    sf::VertexArray va(sf::TriangleFan);
    auto incr = PI2()/nVert;
    for (int k=0; k<nVert; ++k) {
        auto vert = sf::Vertex(sf::Vector2f(radius*cos(k*incr),radius*sin(k*incr)));
        vert.color = color;
        va.append(vert);
    }
    //va.append(va[0]);
    return va;
}

inline float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

inline float project(const sf::Vector2f& vec1, const sf::Vector2f& vec2) noexcept {
    return dot(vec1,vec2)/sqrt(dot(vec2,vec2));
}
